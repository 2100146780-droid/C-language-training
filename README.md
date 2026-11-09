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
│   └── guess_number_annotated.c   猜数字程序的知识点全解
└── src/                           每日练习源码
    ├── hello.c                    环境验证：第一个 Hello World
    ├── flow_light.c               流水灯模拟（位运算热身）
    ├── guess_number.c             d01 猜数字游戏
    └── score_statistics.c         d02 成绩统计器
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

## 进度

| 日期 | 题目 | 完成 |
|---|---|---|
| 2026-11-08 | d01 猜数字游戏 | ✅ |
| 2026-11-09 | d02 成绩统计器 | ✅ |
