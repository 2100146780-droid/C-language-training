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
│   └── d03_pattern_annotated.c    打印图形的知识点全解（嵌套循环核心）
└── src/                           每日练习源码
    ├── hello.c                    环境验证：第一个 Hello World
    ├── flow_light.c               流水灯模拟（位运算热身）
    ├── d01_guess_number.c         d01 猜数字游戏
    ├── d02_score_statistics.c     d02 成绩统计器
    ├── d03_pattern.c              d03 打印直角三角形
    ├── d04_calculator.c           d04 简易计算器（switch + 边界检查）
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
- **git**：
  - `nothing added to commit` = 忘了 `git add`，commit 只提交暂存区里的东西。
  - `fatal: pathspec 'src/README.md' did not match any files` = 路径写错，README 在仓库根目录不在 src/。先 `git status` 看真实路径。
  - 命令别手滑：`gid`、`gti` 都会报"无法将 xxx 项识别为 cmdlet"。
  - `git add` 成功时**没有任何输出**，安静就是成功。

## 进度

| 日期 | 题目 | 完成 |
|---|---|---|
| 2026-11-08 | d01 猜数字游戏 | ✅ |
| 2026-11-09 | d02 成绩统计器 | ✅ |
| 2026-11-15 | d03 打印直角三角形（简化版）+ Day 7 复盘 | ✅ |
| 2026-11-15 | d04 简易计算器（switch + 除零/非法运算符处理） | ✅ |
