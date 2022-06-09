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

ssize_t my_getline(char** lineptr, size_t* n, FILE* stream)
{
    int c = 0;
    size_t len = 5;
    size_t read_len = 0;
    
    if (NULL == *lineptr)
    {
        rewind(stream);
        *n = 0;
    }
    c = fgetc(stream);
    *lineptr = (char*)malloc(len);
    if (NULL == *lineptr)
    {
        printf("malloc failed!\n");
        return -1;
    }
    
    while(EOF != c)
    {
        if ((read_len+1) >= len)
        {
            len = len << 1;
            *lineptr = (char*)realloc(*lineptr, len);
            if (NULL == *lineptr)
            {
                printf("realloc failed!\n");
                return -1;
            }
            //printf("realloc size %ld\n", len);
        }
       //注意：size至少是2,1个字符加字符串结束符'\0' 
        snprintf((char*)(*lineptr+read_len), 2, "%c", (char)c);
        read_len++;
        c = 0;
        c = fgetc(stream);
        if (('\n' == (char)c))
        {
            snprintf((char*)(*lineptr+read_len), 2, "%c", (char)c);
            //printf("%s\n", *lineptr);
            break;
        }
    }
    
    if(read_len > 0)
    {
        return (read_len - 1);
    }
    else
    {
        return -1;
    }
}

void free_my_getline(char* const lineptr)
{
    if (NULL == lineptr)
    {
        return;
    }
    free(lineptr);
}

int main()
{
    char buf[1024];
    int year = 2022;
    int month = 5;
    int date = 31;

    snprintf(buf, sizeof(buf) - 1, "%d-%d-%d", year, month, date);
    puts(buf);
    //snprintf(buf, 5, "%d-%d-%d", year, month, date);
    //puts(buf);

    FILE *p_file;
    p_file = fopen("kongdong.txt","w+");

    if (NULL == p_file)
    {
        //printf("fopen failed\n");
        perror("fopen()");
        return -1;
    }
    //产生空洞文件
    fseek(p_file, 100L, SEEK_SET);
    //fseek(p_file, 0L , SEEK_END);

    printf("len of kongdong.txt:%ld\n", ftell(p_file));
    fclose(p_file);

    p_file = fopen("temp.txt","r");
    if (NULL == p_file)
    {
        //printf("fopen failed\n");
        perror("fopen()");
        return -1;
    }
    fseek(p_file, 0, SEEK_END);
    
    printf("len of temp.txt:%ld\n", ftell(p_file));
    rewind(p_file);
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
   
    char ss[2];
    ret_s = fgets(ss, 2, p_file);
    fprintf(stdout, "ss:%s\n", ss);

    char* p_string = NULL;
    size_t len = 0;
    
    while(my_getline(&p_string, &len, p_file) >= 0)
    {
        printf("%s", p_string);
    }
    free_my_getline(p_string);

    fclose(p_file);
    fclose(p_file_to_write);

    //可变参数函数
    int sum = get_sum(3, 1, 2, 3);
    printf("sum=%d\n",sum);
    return 0;
}
