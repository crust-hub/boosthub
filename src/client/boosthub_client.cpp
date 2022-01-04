#include "./boosthub_client.h"

pthread_mutex_t client_send_receiver_mutex;

/**
 * @brief 客户端接收线程函数
 *
 */
void *boosthub_client_receiver(void *socket_fd)
{
    int socket = *((int *)socket_fd);
    std::cout << "start receive thread:socket" << socket << "\n";
    //定义缓冲区
    char buffer[512] = {0};
    size_t len;
    printf("receiving...\n");
    while (0 != (len = read(socket, buffer, 511)))
    {
        buffer[len] = '\0';
        // pthread_mutex_lock(&client_send_receiver_mutex);
        printf("%s", buffer);
        // pthread_mutex_unlock(&client_send_receiver_mutex);
        // sleep(1);
    }
    printf("receive over\n");
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
        pthread_mutex_init(&client_send_receiver_mutex, NULL); //收发锁
        pthread_t response;
        int response_id;
        response_id = pthread_create(&response, NULL, boosthub_client_receiver, (void *)&socket_fd);
        sleep(1);
        //允许客户端发送命令行
        shell_sender();
        pthread_mutex_destroy(&client_send_receiver_mutex);
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