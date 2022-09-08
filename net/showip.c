
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main(int argc,char *argv[]){

    struct addrinfo hints,*res,*p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
    if(argc != 2){
        fprintf(stderr,"Usage: showip hostname\n");
        return 1;
    }
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    status = getaddrinfo("www.example.net",NULL,&hints,&res);
    
    printf("IP Address for %s: \n\n", argv[1]);
    
    for(p=res; p!= NULL;p=p->ai_next){
        void *addr; 
        const char *ipver;
        // IPv4
        if (p->ai_family == AF_INET){
            struct sockaddr_in *ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        if (p->ai_family == AF_INET6){
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*) p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family,addr,ipstr,sizeof ipstr);
        printf("%s: %s\n",ipver, ipstr);

    }

    freeaddrinfo(res); // free the linked list
    return 0;
}