#include <stdio.h>
#include <sys/syscall.h>

#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>

#define DBG_NONE 0
#define DBG_FORK 1

#define START_DBG syscall(__x64_sys_my_dbg, DBG_FORK);
#define STOP_DBG syscall(__x64_sys_my_dbg, DBG_NONE);

#define __x64_sys_my_dbg 550

int main()
{
    START_DBG
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("[child process]\n");
        pid_t parent_pid = getppid();
        pid_t self_pid = getpid();
        printf("[child process] parent pid: %d\n", parent_pid);
        printf("[child process] self pid : %d\n", self_pid);
        sleep(5);
        printf("[child process] exit\n");
        exit(111);
    }
    else if (pid > 0)
    {
        printf("[parent process]\n");
        pid_t self_pid = getpid();
        printf("[parent process] self pid : %d\n", self_pid);
        printf("[parent process] child pid : %d\n", pid);
        int stat;
        waitpid(pid, &stat, 0);
        int exit_status = WEXITSTATUS(stat);
        printf("[parent process] child process %d die, with status %d\n", pid, exit_status);
        printf("[parent process] exit\n");
    }
    else
    {
        printf("fork failed!\n");
    }
    STOP_DBG
    return 0;
}