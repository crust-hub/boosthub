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
 * @brief 处理与相应任务执行
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
    if (_argc == 4 && !strcmp(_argv[1], "--server"))
    {
        printf("Server Info: IP %s PORT %s\n", _argv[2], _argv[3]);
        /*net service*/
        boost_socket socket(_argv[2], _argv[3]); //创建本机套接字
        socket.service_start();                  //开始网络对外服务
        return 1;
    }
    if (_argc == 4 && !strcmp(_argv[1], "--shell"))
    {
        printf("Client Info: Trying to connect to the boothub IP %s PORT %s\n", _argv[2], _argv[3]);
        return 1;
    }
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