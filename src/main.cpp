#include <iostream>
#include "./tool/tool.h"
using namespace std;
int main(int argc, char **argv)
{
    /*net service*/
    boost_socket socket;    //创建本机套接字
    socket.service_start(); //开始网络对外服务
    return 0;
}