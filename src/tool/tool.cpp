#include "tool.h"
/**
 * @brief Construct a new tool bucket::tool bucket object
 *
 */
tool_bucket::tool_bucket()
{
    BOOST_LOG = new boost_log();
    ARG_PROCESS = new arg_process();
    FILE_OPERATOR = new file_operator();
}
/**
 * @brief Destroy the tool bucket::tool bucket object
 *
 */
tool_bucket::~tool_bucket()
{
    delete BOOST_LOG;
    delete ARG_PROCESS;
    delete FILE_OPERATOR;
}

/**
 * @brief 网络收发线程函数
 *
 * @param client_socket 新的服务端套接字描述符
 * @return void*
 */
void *socket_process_thread(void *client_socket)
{
    printf("Event: new client thread start\n");
    int client_socket_id = *(int *)client_socket;
    free(client_socket);
    // std::cout<<"开启socket处理线程 client_socket "<<client_socket_id<<"\n";
    //每次接收到请求都因该开辟新的线程 对其做出处理 包括接收数据与发送数据
    //读取内容
    char buffer[512] = {0};
    size_t len = 0;
    tool_bucket TOOL;
    boost_shell SHELL;
    SHELL.set_socket_fd(client_socket_id);
    while (1)
    {
        len = recv(client_socket_id, buffer, sizeof(buffer), 0);
        if (len <= 0)
        {
            close(client_socket_id);
            break;
        }
        buffer[len] = '\0';
        SHELL.run(std::string(buffer));
    }

    TOOL.BOOST_LOG->close();
    printf("Event: client disconnect\n");
    //断开连接
    shutdown(client_socket_id, SHUT_WR);
    close(client_socket_id);
    return (void *)"sucess";
}

/**
 * @brief 服务函数 在其内部开启新的服务线程
 *
 * @param client_socket  客户端套接字
 * @return int 线程开启结果
 */
int new_socket_process_thread(int client_socket)
{
    std::cout << client_socket << std::endl;
    pthread_t thread;
    int *arg = (int *)malloc(sizeof(int));
    *arg = client_socket;
    int create_res = pthread_create(&thread, NULL, socket_process_thread, (void *)arg);
    if (create_res < 0)
    {
        std::cout << "socket线程创建失败\n";
        shutdown(client_socket, SHUT_WR);
        close(client_socket);
    }
    return create_res;
}
