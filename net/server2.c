#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "8080" // the port users will be connecting to
#define BACKLOG 10   // how many pending connections queue will hold

void get_bind_addr_printable(struct addrinfo *servinfo, char* buf, size_t len){

    if (servinfo->ai_family ==AF_INET){ // IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in*)servinfo->ai_addr;
        inet_ntop(servinfo->ai_family,&ipv4->sin_addr,buf,len);
    }else if(servinfo->ai_family == AF_INET6){
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*)servinfo->ai_addr;
         inet_ntop(servinfo->ai_family,&ipv6->sin6_addr,buf,len);
    }
}
void* get_in_addr(struct sockaddr *sa){
    if(sa->sa_family == AF_INET){
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char* args[]){
    struct addrinfo hints, *servinfo, *p;
    int sockfd,new_fd; // listen on sock_fd, new connection on new_fd
    struct sockaddr_storage peer_addr; // connector's address information
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN]; 

    int reuse=1; // reuse address

    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags=AI_PASSIVE; // Socket address is intended for `bind'
    hints.ai_socktype = SOCK_STREAM;

    if((status=getaddrinfo(NULL,PORT,&hints,&servinfo)) != 0){
        perror("server: get addr info error");
        printf("error msg :%s\n",gai_strerror(status));
        exit(1);
    }
    for(p = servinfo; p != NULL; p = p->ai_next){
        if((sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1){
            perror("server: socket error");
            continue;
        }
        // 重用地址
        if(setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse) == -1){
            perror("server: setsockopt error");
            exit(1);
        }


        if(bind(sockfd,servinfo->ai_addr,servinfo->ai_addrlen)==-1){
            close(sockfd);
            perror("server: bind error");
            continue;
        }
        // bind success


        get_bind_addr_printable(p, s ,sizeof s);
        printf("server: bind address %s\n",s);
        break;
    }

    freeaddrinfo(servinfo); // all done with this structure
    
    // 循环完了没有一个bind成功
    if(p == NULL){
        fprintf(stderr,"server: failed to bind\n");
        exit(1);
    }

    if(listen(sockfd,BACKLOG)==-1){
        perror("server: listen error");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1){ // main accept() loop
        sin_size = sizeof peer_addr;
        new_fd = accept(sockfd, (struct sockaddr*)&peer_addr, &sin_size);
        if(new_fd == -1){
            perror("server: accept error");
            continue;
        }
        inet_ntop(peer_addr.ss_family,get_in_addr((struct sockaddr *)&peer_addr),s,sizeof s);
        printf("server: got connection from %s\n", s);

        // 如果是父进程fork返回子进程的pid
        // 如果是子进程fork返回0
        // 父进程和子进程都是从fork继续往下执行(不是从头执行)。
        if(!fork()){ // 这是子进程
            close(sockfd); // 子进程不需要监听
            if(send(new_fd,"Hello, world!", 13, 0)==-1){
                perror("send");
            }
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }
    return 0;
}