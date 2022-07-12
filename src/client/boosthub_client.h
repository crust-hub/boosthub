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
#include <utility>

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
    static std::pair<size_t, size_t> get_file_size_check(char *buffer, size_t len)
    {
        //寻找首个\n\n
        size_t target = 0;
        for (; target <= len - 2; target++)
        {
            if (buffer[target] == '\n' && buffer[target + 1] == '\n')
            {
                break;
            }
        }
        if (target == 0)
        {
            return std::pair<size_t, size_t>(-1, -1);
        }
        //如果target不为0则取其前面的内容进行分析
        //$$size$$number\n\n
        if (!(buffer[0] == '$' && buffer[1] == '$' && buffer[2] == 's' && buffer[3] == 'i' && buffer[4] == 'z' && buffer[5] == 'e' && buffer[6] == '$' && buffer[7] == '$' && buffer[target] == '\n' && buffer[target + 1] == '\n'))
        {
            return std::pair<size_t, size_t>(-1, -1);
        }
        for (size_t i = 8; i < target; i++)
        {
            if (!isalnum(buffer[i]))
            {
                return std::pair<size_t, size_t>(-1, -1);
            }
        }
        //将字符串转变为数字
        char file_size_str[512] = {'\0'};
        size_t i = 8;
        for (i = 8; i < target; i++)
        {
            file_size_str[i - 8] = buffer[i];
        }
        file_size_str[i - 8] = '\0';
        long size = atol(file_size_str);
        //将协议头部分的内容从buffer中去掉
        for (size_t i = target + 1; i < len; i++)
        {
            buffer[i - target - 1] = buffer[i];
        }
        return std::pair<size_t, size_t>(size, len - target - 2);
    }
};
#endif
