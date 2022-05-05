#include <iostream>
#include <unistd.h>
#include <string>
#include "config/config.h"
#include "server/server.h"
int main(int argc, char **argv)
{
    Config config;
    config.parse(argc, argv);
    std::cout << config << std::endl; //输出命令行解析内容
    //创建Server实例
    Server server;
    return 0;
}