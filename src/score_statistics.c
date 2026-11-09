/*
 stdin 连续读入 10 个成绩（0~100 的整数），输出：
平均分（保留 1 位小数）
最高分
不及格人数（< 60）
及格率（百分比，保留 0 位小数）
嵌入式关联：这本质上就是传感器采样统计——采 10 个 ADC 值，算均值、找峰值、数异常样本。逻辑一模一样，只是换了皮。
*/
#include<stdio.h>

#define COUNT 10        

int main(void)
{
    int sum=0;
    int max;            /* 初值来自 score[0]，这里故意不填 */
    int fail = 0;
    int score[COUNT];

    printf("please input %d scores:\n",COUNT);   

    for(int i=0;i<COUNT;i++)
    {
        scanf("%d",&score[i]);
    }   

    max=score[0];   

    for(int i=0;i<COUNT;i++)
    {
        sum += score[i];        /* 累加求和，漏了这句平均分恒为 0 */
        if(score[i]>max)
        {   
            max=score[i];          
        }
        if(score[i]<60)
        {
            fail++;
        }
    }

    printf("平均分：%.1f\n",(double)sum/COUNT);
    printf("最高分：%d\n",max);
    printf("不及格人数：%d\n",fail);
    printf("及格率：%.0f%%\n",(COUNT-fail)*100.0/COUNT);    

    return 0;       

}