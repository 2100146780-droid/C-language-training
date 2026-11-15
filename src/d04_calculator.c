#include<stdio.h>

int main (void)
{
    int a,b,result;
    char op;
    //收数据
    scanf("%d %c %d",&a,&op,&b);
    //分发
    switch(op)
    {
        case'+':
        result = a+b;
        break;
        case'-':
        result = a-b;
        break;
        case'*':
        result = a*b;
        break;
        case'/':
        if(b==0)
        {
            printf("error:除数不能为0\n");
            return 0;
        }
        else 
        {       
        result = a/b;
        }
        break;
        default:
        printf("error:运算符不合法\n"); 
        return 0;
    }
//输出
    printf("result = %d\n",result);

    return 0;

}



