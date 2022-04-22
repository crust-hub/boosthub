#include "./boosthub_client.h"
#include "../tool/tool_bucket.h"
#include <cstring>

extern tool_bucket boosthub_tool_bucket;

pthread_mutex_t get_receiver_mutex;

/**
 * @brief 客户端接收线程函数
 *
 */
void *boosthub_client_receiver(void *socket_fd)
{
    char str[100] = {'\0'};
    int socket = *((int *)socket_fd);
    sprintf(str, "start receive thread:socket %d", socket);
    boosthub_tool_bucket.BOOST_LOG->info(str);
    //定义缓冲区
    char buffer[512] = {0};
    size_t len;
    sprintf(str, "receiving working...");
    boosthub_tool_bucket.BOOST_LOG->info(str);
    bool receive_state = 1; //接受工作状态
    while (receive_state && 0 != (len = read(socket, buffer, 511)))
    {
        buffer[len] = '\0';
        // pthread_mutex_lock(&client_send_receiver_mutex);
        // pthread_mutex_unlock(&client_send_receiver_mutex);
        // sleep(1);
        size_t file_size = boosthub_client::get_file_size_check(buffer);
        if (file_size != -1)
        {
            sprintf(str, "有文件要接收大小为 %zd", file_size);
            boosthub_tool_bucket.BOOST_LOG->info(str);
        }
        else
        {
            printf("\n[**%d**]:%s", len, buffer);
        }
    }
    sprintf(str, "receive work over");
    boosthub_tool_bucket.BOOST_LOG->info(str);
}

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
        pthread_mutex_init(&get_receiver_mutex, NULL); //收文件锁
        pthread_t response;
        int response_id;
        response_id = pthread_create(&response, NULL, boosthub_client_receiver, (void *)&socket_fd);
        sleep(1);
        //允许客户端发送命令行
        shell_sender();
        pthread_mutex_destroy(&get_receiver_mutex); //销毁收文件锁
        // void *retavl;
        //  pthread_join(response, &retavl);
    }
    return 0;
}

/**
 * @brief 命令行发送器 主进程
 *
 */
void boosthub_client::shell_sender()
{
    //定义缓冲区
    char buffer[512] = {0};
    size_t len = 0;
    while (0 != strcmp(buffer, "exit"))
    {
        // pthread_mutex_lock(&client_send_receiver_mutex);
        gets(buffer);
        len = strlen(buffer);
        write(socket_fd, buffer, len);
        // pthread_mutex_unlock(&client_send_receiver_mutex);
        // sleep(1);
    }
    std::cout << "exit shell...\n";
    close(socket_fd);
}
