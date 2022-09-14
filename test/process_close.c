#include<stdio.h>	//printf()打印输出
#include<stdlib.h>	//exit()结束进程
#include<assert.h>	//assert()断言
#include<unistd.h>	//宏
#include<fcntl.h>	//I/O函数
void main()
{
    int i = 0;	//遵循C89标准，所有变量必须在main函数开始处进行声明
    int fd = open("./a.txt",O_RDONLY);	//以只读的方式打开，返回文件描述符
    int num = 0;
    char buff[11]={0};
    if(fd == -1)
    {
        printf("Open a.txt failure in reading!");
        exit(1);	//不正常退出
    }
    pid_t  n = fork();
    if(n == 0)
    {
        printf("child process fd: %d \n",fd);
	    close(fd);
    }
    else
    {
        printf("parent process fd: %d \n",fd);
        sleep(100);
        while(1)
        {
            num = read(fd, buff + i*5, 5);
            if(num <= 0)
                break;
            ++i;
        }
        printf("%s\n", buff);
    }
    exit(0);	//正常退出
}