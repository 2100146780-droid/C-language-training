#include<stdio.h>

int main (void)
{
    int a,b,result;   // a：第一个数字，b：第二个数字，result：存放计算结果
    char op;          // op：用来存运算符 + - * /

    // 接收用户输入，格式例子：5 + 3
    scanf("%d %c %d",&a,&op,&b);

    // switch 根据运算符 op 分支选择对应的计算逻辑
    switch(op)
    {
        case '+':         // 如果运算符是加号
            result = a+b;
            break;        // break：跳出switch，防止继续往下执行其他case

        case '-':         // 如果运算符是减号
            result = a-b;
            break;

        case '*':         // 如果运算符是乘号
            result = a*b;
            break;

        case '/':         // 如果运算符是除号
            if(b==0)      // 判断除数是不是0，0不能做除法
            {
                printf("error:除数不能为0\n");
                return 0; // 直接结束程序
            }
            else 
            {        
                result = a/b;
            }
            break;

        default:          // default：上面所有case都不匹配时执行（非法运算符）
            printf("error:运算符不合法\n"); 
            return 0;     // 直接结束程序
    }

    // 输出最终计算结果
    printf("result = %d\n",result);

    return 0;
}
