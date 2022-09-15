#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#define PORT "3490"
int main(int argc, char * args[]){

    struct addrinfo hints;
    struct addrinfo *servinfo;
    int status;
    int sockfd,newfd;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len = sizeof peer_addr;
    char peer_addr_str[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    status = getaddrinfo(NULL, PORT, &hints, &servinfo);
    // 0 if success, or one of the following nonzero error codes
    if(status != 0){
        fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(status));
        return 1;
    }
    sockfd = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);
    // -1 on error
    if(sockfd == -1){
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        return 1;
    }
    int reuse=1;
    status = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof reuse);
    if(status == -1){
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        return 1;
    }
    status = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    if (status == -1){
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        return 1;
    }

    status = listen(sockfd, 20);
    if (status == -1){
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        return 1;
    }
    

    newfd = accept(sockfd, (struct sockaddr *)&peer_addr, &peer_addr_len);
    

    if(peer_addr.ss_family == AF_INET){
        struct sockaddr_in *peer_addr_in = (struct sockaddr_in*)&peer_addr;
        inet_ntop(AF_INET, &(peer_addr_in->sin_addr), peer_addr_str, sizeof peer_addr_str);
        printf("peer addr : %s\n",peer_addr_str);
    }

    // 发送消息给对端
    char *msg = "Server: Hello Client!";
    int bytes_sent = 0;
    int len = strlen(msg);
    int remained;
    do{
        remained = len - bytes_sent;
        if (remained > 0){
            bytes_sent += send(newfd, msg + bytes_sent, remained, 0);
            printf("发送的字节数: %d,剩余的字节数：%d\n",bytes_sent,len - bytes_sent);
        }
    } while(remained);
     FILE *a;
    shutdown(sockfd,2);
    close(sockfd);
    return 0;
}