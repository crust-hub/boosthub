#include "arg_process.h"

arg_process::arg_process()
{
    _argc = 0;
    _argv = nullptr;
}

/**
 * @brief Construct a new arg process::arg process object
 *
 * @param argc 参数个数
 * @param argv 参数内容
 */
arg_process::arg_process(int argc, char ***argv)
{
    _argc = argc;
    _argv = *(argv);
}

/**
 * @brief 处理与相应任务执行boosthub-cli
 *
 * @return int
 */
int arg_process::process()
{
    if (_argc == 0 || _argv == nullptr || _argc == 1)
    {
        result_none();
        return this->ERROR;
    }
    //开启服务端
    if (_argc == 4 && !strcmp(_argv[1], "--server"))
    {
        printf("Server Info: IP %s PORT %s\n", _argv[2], _argv[3]);
        /*net service*/
        boost_socket socket(_argv[2], _argv[3]); //创建本机套接字
        socket.service_start();                  //开始网络对外服务 进程进入循环accept监听
        return 1;
    }
    //客户端shell
    if (_argc == 4 && !strcmp(_argv[1], "--shell"))
    {
        printf("Client Info: Trying to connect to the boothub IP %s PORT %s\n", _argv[2], _argv[3]);
        boosthub_client BOOSTHUB_CLIENT(_argv[2], _argv[3]); //将ip与端口给客户端服务
        BOOSTHUB_CLIENT.connect_server();                    //连接服务器并运行发主进程与收线程
        return 1;
    }
    // cli-help帮助文档
    if (_argc == 2 && !strcmp(_argv[1], "--help"))
    {
        result_none();
        return 1;
    }
    result_none();
    return this->DOWNLOADFILE;
}

void arg_process::result_none()
{
    std::cout << "BOOSTHUB V1.1.1 HELP\n";
    std::cout << "--help                 View help documentation\n";
    std::cout << "--server [ip] [port]   Open external service IP: local listening IP address port: local listening port\n";
    std::cout << "--shell  [ip] [port]   Open the client command line tool IP: server IP address port: server port number\n";
}