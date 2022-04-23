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
#include <cctype>

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
    // get 协议头部解析
    size_t static get_file_size_check(char *buffer)
    {
        int len = strlen(buffer);
        if (len < 11)
        {
            // std::cout << "length" << std::endl;
            return -1;
        }
        //$$size$$number\n\n
        if (!(buffer[0] == '$' && buffer[1] == '$' && buffer[2] == 's' && buffer[3] == 'i' && buffer[4] == 'z' && buffer[5] == 'e' && buffer[6] == '$' && buffer[7] == '$' && buffer[len - 1] == '\n' && buffer[len - 2] == '\n'))
        {
            // std::cout << "limit" << std::endl;
            return -1;
        }
        for (int i = 8; i <= len - 3; i++)
        {
            if (!isalnum(buffer[i]))
            {
                // std::cout << "num limit" << std::endl;
                return -1;
            }
        }
        //将字符串转变为数字
        char file_size_str[512] = {'\0'};
        buffer[len - 2] = '\0';
        size_t i = 8;
        for (i = 8; i < strlen(buffer); i++)
        {
            file_size_str[i - 8] = buffer[i];
        }
        file_size_str[i - 8] = '\0';
        long size = atol(file_size_str);
        return size;
    }
};
#endif
