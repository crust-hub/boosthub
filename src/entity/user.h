#pragma once
#ifndef __USER_H__
#define __USER_H__
#include<string>
class user{
private:
    std::string now_path;//现在的路径
    int socket_fd;
public:
    user();
    void set_nowpath(std::string path);
    std::string get_now_path();
    void set_socket_fd(int fd);
    int get_socket_fd();
};
#endif