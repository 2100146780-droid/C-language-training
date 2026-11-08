/*电脑随机出一个 1~100 的整数
你输入一个数，程序告诉你"大了"或"小了"
猜中了就打印"猜对了！你一共猜了 N 次"
输入 0 直接退出*/
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
int num,times=0,fixed_num;
srand((unsigned)time(NULL));
fixed_num=rand()%100+1;
printf("I have picked a number between 1 and 100,can you guess it?\n");
while(1)
{
printf(" you guess : "); scanf("%d",&num);
times++;
if(num>fixed_num)
{
printf("too big \n");
}
else if(num<fixed_num)
{
printf("too small \n");
}
else if(num==fixed_num)
{
printf("you are right!,you have guessed %d times\n",times);
break;
}
}
return 0;
}
