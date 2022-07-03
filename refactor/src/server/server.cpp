#include "server.h"
using namespace std;

Server::Server()
{
    char work_path[512];
    getcwd(work_path, 512); //获得工作路径
    string path(work_path);
    path += "/static";
    cout << path << endl;
}

Server::~Server()
{
}

void Server::init(int port)
{
    this->port = port;
}

void Server::log_init() //日志初始化
{
}
void Server::db_pool_init() //数据库连接池初始化
{
}
void Server::thread_init() //线程池初始化
{
}
void Server::trig_mode_init() //触发模式初始化
{
}
void Server::event_listen() //监听
{
}
void Server::event_loop() //运行
{
}
