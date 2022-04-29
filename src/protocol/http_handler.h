#ifndef __HTTP_HANDLER__
#define __HTTP_HANDLER__
#include <map>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
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
        const char *body = request_body.c_str();
        std::ofstream outfile;
        outfile.open("./readin.txt", std::ios::out | std::ios::app | std::ios::binary); //输入文件的路径
        outfile << body << std::endl;
        outfile.close(); //调用close（）函数关闭文件
        route_root(socket, http_header, request_body);
        std::cout
            << "HTTP 响应完毕" << std::endl;
    }

private:
    static void route_root(int socket, std::map<std::string, std::string> http_header, std::string request_body)
    {
        // std::cout << request_body << std::endl;
        const char *line1 = "HTTP/1.0 200\n";
        const char *line2 = "Content-Type: text/json\n";
        const char *response_body = "{\"message\":\"hello boosthub server\"}";
        char line3[512];
        sprintf(line3, "Content-Length: %zd\n\n", strlen(response_body));
        write(socket, line1, strlen(line1));
        write(socket, line2, strlen(line2));
        write(socket, line3, strlen(line3));
        write(socket, response_body, strlen(response_body));
    }
};
#endif
//'HTTP/1.1 404' 'Content-Type: text/html' 'Content-Length: 4413' 'Date: Fri, 29 Apr 2022 01:36:05 GMT'