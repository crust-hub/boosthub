#include <iostream>
#include <unistd.h>
#include <string>
#include "config/config.h"
#include "server/server.h"
int main(int argc, char **argv)
{
    Config config;//应用配置类
    config.parse(argc, argv);//解析启动参数
    std::cout << config << std::endl; //输出命令行解析内容
    //创建Server实例
    Server server;
    server.init(8080);
    return 0;
}