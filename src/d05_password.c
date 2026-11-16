#include <stdio.h>

#define MAX_LENGTH  64

int main(void)
{
    int  length = 0;
    int  number = 0, big = 0, small = 0, character = 0;
    char PASSWORD[MAX_LENGTH];
    int  type_count = 0;
    int  i;

    /* 输入：数组名不加 &；%63s 留一格给 '\0' */
    if (scanf("%63s", PASSWORD) != 1)
    {
        printf("error: 没有读到输入\n");
        return 1;
    }

    /* 分析：一趟遍历，一个字符只归一类 */
    for (i = 0; PASSWORD[i] != '\0'; i++)
    {
        if (PASSWORD[i] >= '0' && PASSWORD[i] <= '9')
        {
            number++;
        }
        else if (PASSWORD[i] >= 'A' && PASSWORD[i] <= 'Z')
        {
            big++;
        }
        else if (PASSWORD[i] >= 'a' && PASSWORD[i] <= 'z')
        {
            small++;
        }
        else
        {
            character++;
        }
    }
    length = i;     /* 循环停在 '\0' 上，i 就是实际长度 */

    /* 统计：哪一类出现过就算一种，不必另开 has_ 变量 */
    type_count = (number > 0) + (big > 0) + (small > 0) + (character > 0);

    printf("总长度：%d\n", length);
    printf("数字个数：%d\n", number);
    printf("大写字母个数：%d\n", big);
    printf("小写字母个数：%d\n", small);
    printf("符号个数：%d\n", character);

    if (type_count >= 3 && length >= 8)
    {
        printf("强度：强\n");
    }
    else if (type_count >= 2 && length >= 6)
    {
        printf("强度：中\n");
    }
    else
    {
        printf("强度：弱\n");
    }

    return 0;
}
