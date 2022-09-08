#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
void test1(){
    struct sockaddr_in sa;
    inet_pton(AF_INET,"192.168.56.101",&(sa.sin_addr));
    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET,&(sa.sin_addr),buf,INET_ADDRSTRLEN);
    printf("ip addr: %s\n",buf);
    uint16_t src = 0xFF00;
    uint16_t target = htons(src);
    uint16_t aa = ntohs(target);
    printf("htons : %04x\n",aa);

    printf("test1...\n");

}
void test2(){
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype= SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // fill in my IP for me
    status = getaddrinfo(NULL, "3490", &hints, &servinfo);

    if (status != 0){
        fprintf(stderr,"getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    struct addrinfo *next = servinfo; 
    while (next != NULL){
        // 输出ip地址
        char ip4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(((struct sockaddr_in*)(next->ai_addr))->sin_addr), ip4, INET_ADDRSTRLEN);
        printf("IPv4: %s\n",ip4);
        next = next->ai_next;
    }
   
    freeaddrinfo(servinfo); // free the linked-list
}
void test3(){
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo; // will point to the results
    memset(&hints,0,sizeof hints); // make sure the struct is empt
    // hints.ai_flags = AI_PASSIVE; /* Socket address is intended for `bind'.  */
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    
    // get ready to connect
    status = getaddrinfo("www.example.com","3490",&hints,&servinfo);

}
int main(int argc, char** args){

    // test1();
    // test2();
    // test3();
    return 0;
}