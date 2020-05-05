#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//the head of socket & bind & listen & accept function
#include <sys/socket.h>
//the head of protocol define
#include <arpa/inet.h>
//the head of read & write function
#include <unistd.h>

void error_log(char *message);

int main(int argc, char* argv[]){
    int sock = 0;;
    // the define in <sys/socket.h>
    struct sockaddr_in ser_addr;
    int str_len = 0;
    int ret = 0;
    char message[30];
    if(argc != 3){
        //prarama 0 is the file name
        printf("Usage :%s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        error_log("socket() error");
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    //parama 1 is the address
    ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
    ser_addr.sin_port = htons(atoi(argv[2]));

    //use connect create the socket with sockaddr_in message
    ret = connect(sock, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    if(ret == -1){
        error_log("connect() error");
    }

    //recevie a string to the server
    str_len = read(sock, &message, sizeof(message)-1);
    if(str_len == -1){
        error_log("read() error");
    }

    printf("Recevie the message from server: %s \n", message);
    close(sock);

    return 0;
}

void error_log(char *message){
    //print the error message to the screen
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

