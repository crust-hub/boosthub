#pragma once
#ifndef __USER_H__
#define __USER_H__
#include <string>

//用户实体类
class user
{
private:
    std::string now_path; //用户当前所在路径
    int socket_fd;        //用户套接字描述符

public:
    user();
    void set_nowpath(std::string path); // setter nowpath
    std::string get_now_path();         // getter nowpath
    void set_socket_fd(int fd);         // setter socket_fd
    int get_socket_fd();                // getter socket_fd
};
#endif