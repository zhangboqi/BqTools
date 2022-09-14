/*
*  fork_test.c
*/
 
#include <unistd.h>
#include <stdio.h>
 
int main ()
{
    pid_t pid; //fpid表示fork函数返回的值
    printf("beging....%d\n",getpid());
    // 如果是父进程fork返回子进程的pid
    // 如果是子进程fork返回0
    // 父进程和子进程都是从fork继续往下执行(不是从头执行)。
    pid = fork();
    if (pid < 0)
        printf("error in fork!\n");
    else if (pid == 0)
    {
        printf("i am the child process, my process id is %d\n", getpid());
        printf("我是爹的儿子\n");//对某些人来说中文看着更直白。
    }
    else
    {
        printf("i am the parent process, my process id is %d\n", getpid());
        printf("我是孩子他爹\n");
    }
    return 0;
}