#ifndef __SERVER_H__
#define __SERVER_H__
#include <iostream>
#include <unistd.h>
#include <string>
class Server
{
private:
    int port;

public:
    Server();
    ~Server();
    /**
     * @brief 
     * 
     * @param port 服务器端口号
     */
    void init(const int port);
    void log_init();//日志初始化
    void db_pool_init();//数据库连接池初始化
    void thread_init();//线程池初始化
    void trig_mode_init();//触发模式初始化
    void event_listen();//监听
    void event_loop();//运行
};
#endif