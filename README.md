# C-language-training

C 语言基础训练仓库，30 天每日一练。目标：从"看懂教程代码"过渡到"从空白文件独立写出"，为嵌入式软件岗打地基。

配套主线：STM32 学习在 [hello-stm32](https://github.com/2100146780-droid/hello-stm32) 仓库。

## 仓库结构

```
C-language-training/
├── README.md                      本说明
├── C语言每日一练-30天计划.md       训练计划总表（含进度标记）
├── .gitignore                     忽略编译产物（*.exe 等）
├── notes/                         学习注释版代码（逐行讲解）
│   ├── guess_number_annotated.c   猜数字程序的知识点全解
│   ├── d03_pattern_annotated.c    打印图形的知识点全解（嵌套循环核心）
│   └── d05_password_annotated.c   密码强度的知识点全解（字符串与 '\0'）
└── src/                           每日练习源码
    ├── hello.c                    环境验证：第一个 Hello World
    ├── flow_light.c               流水灯模拟（位运算热身）
    ├── d01_guess_number.c         d01 猜数字游戏
    ├── d02_score_statistics.c     d02 成绩统计器
    ├── d03_pattern.c              d03 打印直角三角形
    ├── d04_calculator.c           d04 简易计算器（switch + 边界检查）
    ├── d05_password.c             d05 密码强度检查（字符遍历）
    └── sum.c                      复习小程序：两数之和
```

## 环境

- 编译器：GCC (MinGW-W64 / WinLibs UCRT)
- 编译运行：`gcc src\文件名.c -o test.exe -fexec-charset=GBK` 然后 `.\test.exe`
  （`-fexec-charset=GBK` 让中文提示在 Windows 默认控制台正常显示）
- 警告全开：`-Wall -Wextra`（已内置到 VS Code 编译任务）
- 版本管理：Git（SSH over 443）

## 踩坑记录

每天一题不是目的，踩坑并记录才是。这里是编译器不会报错、只能靠测试数据抓出来的坑：

- **d01**：`scanf("%d", &x)` 少了 `&` 会段错误；随机数用 `% RANGE + 1` 时注意偏移。
- **d02**：
  - `sum` 忘了累加，平均分恒为 0——遍历循环里每一行都要问自己"这趟循环到底完成了什么"。
  - `sum / COUNT` 是整数除法，小数直接截断（不四舍五入）。浮点结果必须让运算里出现浮点数：`(double)sum / COUNT`。对应 STM32 上 `adc * 3.3f / 4096.0f` 的电压换算。
  - 极值初值要从数据里取（`max = scores[0]`），不能假设 0——数据可能全为负。
  - `Permission denied` 编译失败 = 上一个 exe 进程还在跑，先 Ctrl+C 再重编。
  - 改完源码必须重新编译，否则运行的永远是旧程序。
  - 中文乱码：源码 UTF-8、控制台 GBK，编译参数 `-fexec-charset=GBK` 根治。
- **d03**：
  - 内层循环条件写成 `b <= 5` 输出的是矩形不是三角形——`5` 是总行数（常量），`a` 是当前行号（变量），"每行打几颗"必须跟行号走：`b <= a`。
  - `\n` 必须放在内层循环**外面**，放里面每颗星各占一行。
  - 两个嵌套循环不能共用一个变量，内层每轮必须从初值重新开始。
  - 验证方法：改一个条件编译跑一次看输出变化，比在脑子里推快得多。
- **d04**：
  - 整型除零不会报错，而是**进程直接被系统终止**（PC 上无任何输出，STM32 上进 HardFault）。`if (b == 0)` 必须写在除法**之前**，顺序不可颠倒。
  - 错误分支只 `printf` 不 `return`，末尾的输出语句照样执行 → 打印出 `result = 32759` 这种垃圾值（未初始化的栈内存，不是算出来的）。**错误路径必须提前 return**。
  - 报错时 `return 1`、正常结束 `return 0`——返回值是给外部（脚本 / CI / 调用者）判断成败的错误码约定。
  - `switch` 每个 `case` 结尾都要 `break`，漏了会"贯穿"执行下一个分支的代码。
  - 输入不合法时 `scanf` 读失败，变量保留原值（垃圾值），后续逻辑全部不可信。用 `if (scanf(...) != 3)` 检查读到的项数。
  - `7 / 2` 得 3：整数除法截断，不是 bug，是 C 的规则。
  - 测试时在 PowerShell 里直接敲 `9/0`，是 **PowerShell 自己在算**，报的是它的错；程序输入要用 `.\test.exe` 运行后输入，或 `echo "9 / 0" | .\test.exe`。
- **d05**（这题卡了两小时，坑全在"字符串怎么进来"）：
  - `int PASSWORD[64]` + `scanf("%d", ...)` 是第一个死穴：密码是**字符**不是整数，必须用 `char` 数组。`%d` 读 `"Abc12345"` 会直接失败（返回 0），数组里全是未初始化垃圾。字符本质是 1 字节的小整数，`'A'` 就是 65，所以后面才能用 `ch >= 'A' && ch <= 'Z'` 比较。
  - 输入循环写成 `for (i = 0; i < 64; i++) scanf(...)` 会要求用户输 64 次。字符串一次读完即可：`scanf("%63s", buf)`，长度由结尾的 `'\0'` 决定。
  - `length` 声明了却**从没赋值**，恒为 0 → `length >= 8` 恒假 → 不管输什么都判"弱"。长度是遍历数出来的：`length = i;`（循环停在 `'\0'` 上，此时 `i` 就是字符个数）。编译器不报错，只有跑 `Abc12345` 看到长度是 0 才抓得到。
  - `scanf("%63s", &PASSWORD)` 里的 `&` 是错的：`&数组名` 的类型是 `char (*)[64]`，`-Wall` 直接警告 `expects 'char *'`。地址数值恰好相同，程序照样能跑——**这种"能跑但是错的"最难查**。
  - `number + big + small + character >= 3` 是错的：这个和等于总长度，任何 3 位密码都能过。要的是"出现过几种字符"：`(number > 0) + (big > 0) + (small > 0) + (character > 0)`。比较的结果就是 0/1，可以直接相加，不必再开四个 `has_xxx` 变量——同一份状态别用两套数据存。
  - 强/中/弱写成三个独立 `if` 会同时打印两行："强"成立时"中"的条件必然也成立（3≥2、8≥6）。互斥判定必须用 `if / else if / else` 一条链，且先判最严的。
  - `printf("总长度：%d%d%d%d\n", length, number, big, small, character)` 五个参数配四个 `%d`，且没有分隔符会粘成 `80000`。`-Wall` 会报 `too many arguments for format`——**占位符个数和参数个数要一个个数**。
  - **容量 ≠ 长度**：`MAX_LENGTH`（64）是编译期容量，`length` 是运行期实际长度。对应 STM32 上的 `uint8_t rx_buf[64]` 和 `rx_len`：串口收 5 字节时 `rx_len` 是 5，数组仍是 64 格。这两个混了就会读到上一帧的残渣，或者越界踩坏别的变量。
- **git**：
  - `nothing added to commit` = 忘了 `git add`，commit 只提交暂存区里的东西。
  - `fatal: pathspec 'src/README.md' did not match any files` = 路径写错，README 在仓库根目录不在 src/。先 `git status` 看真实路径。
  - `fatal: pathspec 'src/d5_password.c' did not match any files` = **文件名打错**，真实文件是 `d05_password.c`（少敲一个 0）。凡是 `pathspec ... did not match`，都是"这个路径不存在"，先 `ls src/` 或 `git status` 核对，别凭记忆敲。
  - `git add` 后面什么都不带 → `Nothing specified, nothing added`。add 必须告诉它加什么：文件路径（精确）或 `.`（当前目录全选）。
  - `git commit` **不带 `-m`** 会打开 vim 让你手写信息，新手容易卡死。救命三键：`Esc` → `:q!` → 回车（不保存退出）；`Esc` → `:wq` → 回车（保存退出）。初学一律用 `git commit -m "信息"`。
  - `git add .` 是"当前目录全选"，会把不想提交的东西一起带进暂存区（这天差点把命名错误的 `d2_score_statistics.c` 提交上去）。反悔用 `git restore --staged <文件>`：只退出暂存区，**不动工作目录里的文件内容**，是 `git add` 的逆操作。
  - 一个 commit 只做一件事：d05 的代码和 d01/d03/d04 的注释补充要分开提，否则 `git log` 看不懂、出问题没法精确回滚。
  - `warning: LF will be replaced by CRLF` 是换行符提示，**不是错误**，功能不受影响（Unix 用 LF、Windows 用 CRLF，git 自动转换）。要统一可在根目录加 `.gitattributes`，内容 `* text=auto eol=lf`——后期上 Linux/WSL 交叉编译时省事。
  - 命令别手滑：`gid`、`gti` 都会报"无法将 xxx 项识别为 cmdlet"。
  - `git add` 成功时**没有任何输出**，安静就是成功。

## 进度

| 日期 | 题目 | 完成 |
|---|---|---|
| 2026-11-08 | d01 猜数字游戏 | ✅ |
| 2026-11-09 | d02 成绩统计器 | ✅ |
| 2026-11-15 | d03 打印直角三角形（简化版）+ Day 7 复盘 | ✅ |
| 2026-11-15 | d04 简易计算器（switch + 除零/非法运算符处理） | ✅ |
| 2026-11-16 | d05 密码强度检查（char 数组 + '\0' 遍历 + 分类统计） | ✅ |
