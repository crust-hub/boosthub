#include <cstring>
#include <memory>
#include "./boosthub_client.h"
#include "../tool/tool_bucket.h"
#include "../tool/boosthub_thread.h"

extern tool_bucket boosthub_tool_bucket;

/**
 * @brief Construct a new boosthub client::boosthub client object
 *
 * @param ip 服务端ip地址
 * @param port 服务端boosthub端口号
 */
boosthub_client::boosthub_client(char *ip, char *port)
{
    if (strlen(ip) > 15)
    {
        std::cout << "IP Error\n";
        exit(-1);
    }
    strcpy(server_ip, ip);
    //服务端ip地址
    sscanf(port, "%d", &server_port);
}

/**
 * @brief 尝试连接服务端
 *
 * @return int
 */
int boosthub_client::connect_server()
{
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd == -1)
    {
        printf("create socket error...\n");
        exit(-1);
    }
    else
    {
        printf("create socket success...\n");
    }
    //服务端信息
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(server_port);
    printf("connect server...\n");
    if (0 != connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)))
    {
        printf("connect server error...\n");
        exit(-1);
    }
    else
    {
        printf("connect server success...\n");
        //开启接收线程
        pthread_t response;
        int response_id;
        response_id = pthread_create(&response, NULL, boosthub_thread::boosthub_client_receiver, (void *)&socket_fd);
        sleep(1);
        //允许客户端发送命令行
        shell_sender();
        // void *retavl;
        //  pthread_join(response, &retavl);
    }
    return 0;
}

std::shared_ptr<std::string> boosthub_client_shell_realtime_info = std::make_shared<std::string>("");

/**
 * @brief 命令行发送器 主进程
 *
 */
void boosthub_client::shell_sender()
{
    //定义缓冲区
    std::string buffer = "";
    size_t len = 0;
    while (buffer != "exit")
    {
        //拷贝给全局变量作为收发线程通信数据以便接收数据时做出处理
        *boosthub_client_shell_realtime_info = buffer;
        std::getline(std::cin, buffer);
        len = buffer.length();
        write(socket_fd, buffer.c_str(), len);
    }

    std::cout << "exit shell...\n";
    close(socket_fd);
}
