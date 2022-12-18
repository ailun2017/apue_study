#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

static void sig_cld(int signo)
{
    pid_t pid;
    int status;

    fprintf(2, "sigcld received\n");
    if (signal(SIGCLD, sig_cld) == SIG_ERR)
    {
        perror("signal error");
    }

    if ((pid = wait(&status)) < 0)
    {
        perror("wait error");
    }
    fprintf(2, "pid = %d\n", pid);
}

int main()
{
    pid_t pid;

    if (signal(SIGCLD, sig_cld) == SIG_ERR)
    {
        perror("signal error");
    }

    if ((pid  = fork()) < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        sleep(2);
        _exit(0);
    }
    pause();
    exit(0);
}
