#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int get_sum(int num_of_param, ...)
{
    int loop = 0;
    int sum = 0;
    va_list p_va_list;
    va_start(p_va_list, num_of_param);
    for (loop = 0; loop < num_of_param; loop++)
    {
        sum += va_arg(p_va_list, int);
    }

    va_end(p_va_list);
    return sum;
}

int main()
{
    char buf[1024];
    int year = 2022;
    int month = 5;
    int date = 31;

    snprintf(buf, sizeof(buf) - 1, "%d-%d-%d", year, month, date);
    puts(buf);
    snprintf(buf, 5, "%d-%d-%d", year, month, date);
    puts(buf);

    FILE *p_file;
    p_file = fopen("temp.txt","r");
    if (NULL == p_file)
    {
        printf("fopen failed\n");
        return -1;
    }
    FILE *p_file_to_write;
    p_file_to_write = fopen("temp_copy.txt", "w");
    if (NULL == p_file_to_write)
    {
        printf("fopen failed\n");
        return -1;
    }

    char s[50];

    char* ret_s = fgets(s, 50, p_file);
    while(NULL != ret_s)
    {
        fputs(ret_s, p_file_to_write);
        ret_s = fgets(s, 50, p_file);
    }
    
    fclose(p_file);
    fclose(p_file_to_write);

    //可变参数函数
    int sum = get_sum(3, 1, 2, 3);
    printf("sum=%d\n",sum);
    return 0;
}
