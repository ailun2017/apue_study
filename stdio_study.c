#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buf[1024];
    int year = 2022;
    int month = 5;
    int date = 31;

    snprintf(buf, sizeof(buf) - 1, "%d-%d-%d", year, month, date);
    puts(buf);
    return 0;
}
