#include "./boosthub_thread.h"
#include "../tool/tool_bucket.h"
#include "../protocol/boosthub_http.h"
#include "../protocol/http_handler.h"
#include "../tool/boosthub_buffer.h"
#include "../protocol/http_request.h"
#include <cstdlib>

extern tool_bucket boosthub_tool_bucket;
extern boosthub_http boosthub_http_instance;

/**
 * @brief 网络收发线程函数
 *
 * @param client_socket 新的服务端套接字描述符
 * @return void*
 */
void *boosthub_thread::socket_process_thread(void *client_socket)
{
    int client_socket_id = *(int *)client_socket; //获取客户端套接字
    free(client_socket);                          //在主线程向此线程传递参数使用了堆内存，子线程获取后将其内存释放掉
    boost_shell SHELL;                            //为此socket创建shell处理工具
    SHELL.set_socket_fd(client_socket_id);        // shell 与 服务端id绑定
    //每次接收到请求都因该开辟新的线程 对其做出处理 包括接收数据与发送数据
    //读取内容
    char buffer[512] = {0};
    size_t len = 0;
    boosthub_buffer receive_buffer;
    while (1) //监听客户端发送的内容
    {
        len = recv(client_socket_id, buffer, sizeof(buffer) - 1, 0);
        if (len <= 0) // socket异常或者断开
        {
            close(client_socket_id);
            client_socket_id = -1;
            break;
        }
        buffer[len] = '\0';
        receive_buffer.push_back(buffer, len); //追加到缓冲区内
        // 检测是否为HTTP请求
        std::size_t header_size = boosthub_http_instance.header_check(receive_buffer, 0);
        std::map<std::string, std::string> header = boosthub_http_instance.header_analysis(receive_buffer, header_size);

        if (header.size() != 0) //是http请求
        {
            http_request request(header);
            //判断请求体已经接收了多少字节
            std::size_t body_received_size = receive_buffer.get_length() - header_size; //则已经收到请求体的字节大小为body_received_size
            if (body_received_size == request.content_length)
            {
                request.request_body = receive_buffer.buffer + header_size; //找到请求体在缓存中的开始地址
                http_handler::handle(client_socket_id, request);
            }
            else if (body_received_size > request.content_length) //超出content-length,则拒绝处理此请求，此处暗藏了没有content-length的情况
            {
                receive_buffer.clear(); //清空接收缓存
            }
        }
        else
        {
            SHELL.run(std::string(buffer)); //解析命令行 向客户端响应
        }
    }
    boosthub_tool_bucket.BOOST_LOG->info("Event: client disconnect");
    //断开连接
    if (client_socket_id != -1)
    {
        shutdown(client_socket_id, SHUT_WR);
        close(client_socket_id);
    }
    return (void *)"sucess";
}

/**
 * @brief 为请求创建新的线程
 *
 * @param client_socket  accept得到的客户端套接字
 * @return int 线程开启结果
 */
int boosthub_thread::new_socket_process_thread(int client_socket)
{
    char info[200] = {'\0'};
    sprintf(info, "new client socket %d", client_socket);
    boosthub_tool_bucket.BOOST_LOG->info(info);
    //创建新的socket_process_thread线程任务
    pthread_t thread;
    int *arg = (int *)malloc(sizeof(int));
    *arg = client_socket;
    int create_res = pthread_create(&thread, NULL, boosthub_thread::socket_process_thread, (void *)arg);
    //线程创建失败
    if (create_res < 0)
    {
        sprintf(info, "new boosthub_thread::socket_process_thread thread create failed");
        boosthub_tool_bucket.BOOST_LOG->error(info);
        shutdown(client_socket, SHUT_WR); //与客户端套接字断开
        close(client_socket);             //关闭套接字
    }
    return create_res; //返回线程创建状态
}

/**
 * @brief 客户端接收时不允许客户端向服务端发送内容，用于客户端的接收线程与主线程的同步
 *
 */
pthread_mutex_t get_receiver_mutex;

/**
 * @brief 为客户端开启socket接收线程
 *
 * @param socket_fd 客户端创建的socket
 * @return void*
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