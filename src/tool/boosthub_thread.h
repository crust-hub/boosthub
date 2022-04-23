#include <pthread.h>
/**
 * @brief thread function
 *
 */
namespace boosthub_thread
{
    //线程函数
    void *socket_process_thread(void *client_socket);
    //对外服务函数
    int new_socket_process_thread(int client_socket);
    //客户端线程函数
    void *boosthub_client_receiver(void *socket_fd);
}