#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

static void my_alarm(int signum)
{
    struct passwd* ptr;
    printf("alarm signal handler\n");
    if ((ptr = getpwnam("jack")) == NULL)
    {
        perror("getpwnam error");
    }
    alarm(1);
}

int main(void)
{
    struct passwd* ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    while(1)
    {
        if ((ptr = getpwnam("jack")) == NULL)
            perror("getpwnam error");
        if (strcmp(ptr->pw_name, "jack") != 0)
        {
            printf("return value error!, pw_name = %s\n", ptr->name);
        }
    }
    return 0;
}
