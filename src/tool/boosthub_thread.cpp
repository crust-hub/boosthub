#include "./boosthub_thread.h"
#include "../tool/tool_bucket.h"

extern tool_bucket boosthub_tool_bucket;

/**
 * @brief 网络收发线程函数
 *
 * @param client_socket 新的服务端套接字描述符
 * @return void*
 */
void *boosthub_thread::socket_process_thread(void *client_socket)
{
    boosthub_tool_bucket.BOOST_LOG->info("Event: new client thread start");
    int client_socket_id = *(int *)client_socket;
    free(client_socket);
    // std::cout<<"开启socket处理线程 client_socket "<<client_socket_id<<"\n";
    //每次接收到请求都因该开辟新的线程 对其做出处理 包括接收数据与发送数据
    //读取内容
    char buffer[512] = {0};
    size_t len = 0;
    tool_bucket TOOL;
    boost_shell SHELL;
    SHELL.set_socket_fd(client_socket_id); // shell 与 服务端id绑定
    while (1)
    {
        len = recv(client_socket_id, buffer, sizeof(buffer), 0);
        if (len <= 0)
        {
            close(client_socket_id);
            break;
        }
        buffer[len] = '\0';
        boosthub_tool_bucket.BOOST_LOG->info(buffer);
        SHELL.run(std::string(buffer)); //解析命令行 向客户端响应
    }
    boosthub_tool_bucket.BOOST_LOG->close();
    boosthub_tool_bucket.BOOST_LOG->info("Event: client disconnect");
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
int boosthub_thread::new_socket_process_thread(int client_socket)
{
    std::cout << client_socket << std::endl;
    pthread_t thread;
    int *arg = (int *)malloc(sizeof(int));
    *arg = client_socket;
    int create_res = pthread_create(&thread, NULL, boosthub_thread::socket_process_thread, (void *)arg);
    if (create_res < 0)
    {
        std::cout << "socket线程创建失败\n";
        shutdown(client_socket, SHUT_WR);
        close(client_socket);
    }
    return create_res;
}

pthread_mutex_t get_receiver_mutex;

/**
 * @brief 客户端接收线程函数
 *
 */
void *boosthub_thread::boosthub_client_receiver(void *socket_fd)
{
    char str[100] = {'\0'};
    int socket = *((int *)socket_fd);
    sprintf(str, "start receive thread:socket %d", socket);
    boosthub_tool_bucket.BOOST_LOG->info(str);
    //定义缓冲区
    char buffer[5120] = {0};
    size_t len;
    sprintf(str, "receiving working...");
    boosthub_tool_bucket.BOOST_LOG->info(str);
    bool receive_state = 1; //接受工作状态
    size_t receive_count = 0;
    size_t should_receive_count = 0;
    float receive_processing = 0;
    while (receive_state && 0 != (len = read(socket, buffer, 5119)))
    {
        buffer[len] = '\0';
        // pthread_mutex_lock(&client_send_receiver_mutex);
        // pthread_mutex_unlock(&client_send_receiver_mutex);
        // sleep(1);
        long file_size = boosthub_client::get_file_size_check(buffer);
        if (file_size > 0)
        {
            should_receive_count = file_size; //需要接收多大
            receive_count = 0;                //清空已经接受计数
            sprintf(str, "waiting receive %zd", file_size);
            boosthub_tool_bucket.BOOST_LOG->info(str);
        }
        else
        {
            if (should_receive_count != 0)
            {
                receive_count += len;
            }
            if (should_receive_count != 0) //接收文件状态
            {
                float processing = ((float)receive_count / (float)should_receive_count) * 100;
                if (processing - receive_processing > 0.97)
                {
                    receive_processing = processing; // update process
                    std::cout << "processing " << processing << " % " << std::endl;
                }
            }
            else // shell 相应状态
            {
                printf("%s", buffer);
            }
            // std::cout << "receive_count " << receive_count << " should_receive_count " << should_receive_count << std::endl;
            if (receive_count >= should_receive_count)
            {
                receive_count = 0; //清空已经接受计数
                should_receive_count = 0;
                receive_processing = 0; //接收进度回0
                sprintf(str, "there a receive over");
                boosthub_tool_bucket.BOOST_LOG->info(str);
            }
        }
        buffer[0] = '\0';
    }
    sprintf(str, "receive work over");
    boosthub_tool_bucket.BOOST_LOG->info(str);
    sprintf(str, "main process exit");
    boosthub_tool_bucket.BOOST_LOG->info(str);
    close(socket);
    exit(0);
}