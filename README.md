# C-language-training

C 语言基础训练仓库，30 天每日一练。目标：从"看懂教程代码"过渡到"从空白文件独立写出"，为嵌入式软件岗打地基。

配套主线：STM32 学习在 [hello-stm32](https://github.com/2100146780-droid/hello-stm32) 仓库。

## 仓库结构

```
C-language-training/
├── README.md                      本说明
├── C语言每日一练-30天计划.md       训练计划总表（含进度标记）
├── notes/                         学习注释版代码（逐行讲解）
│   └── guess_number_annotated.c   猜数字程序的知识点全解
└── src/                           每日练习源码
    ├── d01 猜数字游戏              while / if-else / scanf / 随机数
    └── ...
```

## 环境

- 编译器：GCC (MinGW-W64 / WinLibs UCRT)
- 编译运行：`gcc src\文件名.c -o test.exe` 然后 `.\test.exe`
- 版本管理：Git（SSH over 443）

## 进度

| 日期 | 题目 | 完成 |
|---|---|---|
| 2026-11-08 | d01 猜数字游戏 | ✅ |
