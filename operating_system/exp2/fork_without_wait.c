#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("[child process]\n");
        pid_t parent_pid = getppid();
        pid_t self_pid = getpid();
        printf("[child process] parent pid: %d\n", parent_pid);
        printf("[child process] self pid : %d\n", self_pid);
        for (int i = 1; i < 10; i++) for (int j = 1; j > 0; j++);
        printf("[child process] exit");
    }
    else if (pid > 0)
    {
        printf("[parent process]\n");
        pid_t self_pid = getpid();
        printf("[parent process] self pid : %d\n", self_pid);
        printf("[parent process] child pid : %d\n", pid);
        for (int i = 1; i < 5; i++) for (int j = 1; j > 0; j++);
        printf("[parent process] exit\n");
    }
    else
    {
        printf("fork failed!\n");
    }
    return 0;
}