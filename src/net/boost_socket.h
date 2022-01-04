#pragma once
#ifndef __BOOST_SOCKET_H__
#define __BOOST_SOCKET_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
class boost_socket
{
private:
    //本机套接字
    int server_socket_id;
    //创建本机信息结构体
    struct sockaddr_in server_address;
    //客户端
    struct sockaddr_in client_address;

public:
    boost_socket();
    ~boost_socket();
    void service_start();
};
#endif