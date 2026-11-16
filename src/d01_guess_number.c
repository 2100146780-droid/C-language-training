#include<stdio.h>   // 标准输入输出库，用来printf打印、scanf读取键盘输入
#include <stdlib.h> // 标准工具库，rand()随机函数需要这个头文件
#include <time.h>   // 时间库，获取当前时间，用来设置随机数种子

int main(void)
{
    int num,times=0,fixed_num; 
    // num：存放你每次猜的数字
    // times：记录猜的次数，初始为0
    // fixed_num：电脑随机生成的目标数字

    srand((unsigned)time(NULL)); 
    // 设置随机数种子：用当前系统时间当种子，保证每次运行随机数不一样
    // 如果不写这句，每次运行程序出来的随机数都会是同一套

    fixed_num=rand()%100+1; 
    // rand() 得到一个很大的随机整数
    // rand()%100 对100取余，结果范围是 0~99
    // +1 之后范围变成 1~100，正好符合题目要求

    printf("I have picked a number between 1 and 100,can you guess it?\n");
    // 提示：我已经选好了一个1到100之间的数字，你来猜猜看

    while(1)  
    // 无限循环，while括号里为1代表条件永远成立，一直循环
    // 只有遇到break才会跳出循环
    {
        printf(" you guess : "); 
        scanf("%d",&num);  // 接收你从键盘输入的数字，存到变量num里
        times++;           // 猜一次，次数+1

        if(num>fixed_num)  // 如果你猜的数 > 目标数字
        {
            printf("too big \n");  // 提示：大了
        }
        else if(num<fixed_num)   // 如果你猜的数 < 目标数字
        {
            printf("too small \n"); // 提示：小了
        }
        else if(num==fixed_num)  // 猜对了，两个数字相等
        {
            printf("you are right!,you have guessed %d times\n",times);
            // 输出猜对提示，并打印一共猜了多少次
            break; // 跳出while死循环，游戏结束
        }
    }
    return 0; // main函数正常结束，返回0
}
