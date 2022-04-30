#include "boost_socket.h"
#include <iostream>
#include "../tool/tool_bucket.h"
#include "../tool/boosthub_thread.h"

extern tool_bucket boosthub_tool_bucket;

/**
 * @brief Construct a new boost socket::boost socket object
 *
 * @param ip 监听ip地址
 * @param port 监听端口
 */
boost_socket::boost_socket(char *ip, char *port)
{
    //创建TCP本机套接字
    server_socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (0 >= server_socket_id)
    {
        std::cout << "创建套接字失败";
        exit(-1);
    }
    //重置本机信息
    memset(&this->server_address, 0, sizeof(this->server_address));
    memset(&this->client_address, 0, sizeof(this->client_address));
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_addr.s_addr = inet_addr(ip);
    int port_num = 1234;
    sscanf(port, "%d", &port_num);                   //将端口字符串转换为整数端口
    this->server_address.sin_port = htons(port_num); // server port
    //将本机信息绑定到套接字
    bind(server_socket_id, (struct sockaddr *)&this->server_address, sizeof(this->server_address));
    //开始监听端口
    if (-1 == listen(server_socket_id, 20))
    {
        printf("端口监听失败 Ip Error Or Port Error");
        exit(-1);
    }
}

/**
 * @brief 开启对外服务监听
 *
 */
void boost_socket::service_start()
{
    socklen_t client_address_size = sizeof(this->client_address);
    while (1)
    {
        memset(&(this->client_address), 0, sizeof(this->client_address));
        //阻塞accept
        int client_socket_id = accept(server_socket_id,
                                      (struct sockaddr *)&(this->client_address),
                                      &client_address_size);
        //与服务端连接成功
        if (client_socket_id >= 0)
        {
            // std::cout << "接收请求" << client_socket_id << "\n";
            boosthub_thread::new_socket_process_thread(client_socket_id); //开启线程函数为新的client提供服务
        }
        else
        {
            std::cout << "accept 返回 -1\n";
            // break;
        }
    }
}

boost_socket::~boost_socket()
{
    close(server_socket_id); //关闭本机套接字
}
