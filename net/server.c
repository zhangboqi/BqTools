#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
int main(int argc, char * args[]){

    struct addrinfo hints;
    struct addrinfo *servinfo;
    int status;
    int sockfd,newfd;
    socklen_t addr_size;
    struct sockaddr_storage their_addr;

    memset(&hints, 0, sizeof hints);
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    status = getaddrinfo(NULL, "3490", &hints, &servinfo);
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

    status = listen(sockfd,20);
    if (status == -1){
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        return 1;
    }
    addr_size = sizeof their_addr;

    newfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    char *msg = "Server: Hello Client!";
    int bytes_sent = 0;
    int len = strlen(msg);
    int remained;
    do{
        remained = len - bytes_sent;
        if (remained > 0){

            bytes_sent += send(newfd, msg + bytes_sent, len - bytes_sent, 0);
        }
    }while(remained);


    return 0;
}