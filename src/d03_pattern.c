/*
        直角三角形
*/ 
#include<stdio.h>

int main(void)
{
    int a,b;

    for(a=1;a<=5;a++)
    {
        for(b=1;b<=a;b++)
        {
            printf("*");
        }
        
        printf("\n");        
    }

return 0;

}

