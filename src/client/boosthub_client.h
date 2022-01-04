#pragma once
#ifndef __BOOSTHUB_CLIENT_H__
#define __BOOSTHUB_CLIENT_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <error.h>

//接收线程函数
void *boosthub_client_receiver(void *socket_fd);
//客户端
class boosthub_client
{
private:
    char server_ip[20];     //服务端ip地址
    int server_port = 1234; //服务端端口号
    int socket_fd;          //套接字描述符
    void shell_sender();    //命令行发送器 主进程

public:
    boosthub_client(char *ip, char *port);
    int connect_server();
};
#endif
