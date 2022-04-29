#ifndef __HTTP_HANDLER__
#define __HTTP_HANDLER__
#include <map>
#include <string>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
class http_handler
{
public:
    /**
     * @brief http响应处理入口
     *
     * @param socket socket文件标识符
     * @param http_header http请求头部信息
     * @param body http请求体
     */
    static void handle(int socket, std::map<std::string, std::string> http_header, std::string request_body)
    {
        std::cout
            << "HTTP 处理中" << std::endl;
        route_root(socket, http_header, request_body);
        std::cout
            << "HTTP 响应完毕" << std::endl;
    }

private:
    static void route_root(int socket, std::map<std::string, std::string> http_header, std::string request_body)
    {
        std::cout << request_body << std::endl;
        const char *line1 = "HTTP/1.0 200\n";
        const char *line2 = "Content-Type: text/json\n";
        std::cout << 1 << std::endl;
        const char *response_body = "{\"message\":\"hello boosthub server\"}";
        char line3[512];
        std::cout << 2 << std::endl;
        sprintf(line3, "Content-Length: %zd\n\n\0", strlen(response_body));
        std::cout << 3 << std::endl;
        write(socket, line1, strlen(line1));
        std::cout << 4 << std::endl;
        write(socket, line2, strlen(line2));
        std::cout << 5 << " " << strlen(line3) << std::endl;
        write(socket, line3, strlen(line3));
        std::cout << 6 << std::endl;
        write(socket, response_body, strlen(response_body));
        std::cout << 7 << std::endl;
    }
};
#endif
//'HTTP/1.1 404' 'Content-Type: text/html' 'Content-Length: 4413' 'Date: Fri, 29 Apr 2022 01:36:05 GMT'