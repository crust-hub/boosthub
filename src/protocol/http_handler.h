#ifndef __HTTP_HANDLER__
#define __HTTP_HANDLER__
#include <map>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sys/socket.h>
#include "../protocol/http_request.h"
#include "../file/file_operator.h"
#include "../tool/boosthub_time.h"

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
    static void handle(int socket, http_request request)
    {
        if (request.content_length > 0)
        {
            const char *body = request.request_body;
            file_operator FILE_OPERATOR;
            char boosthub_path[1024] = "\0";
            FILE_OPERATOR.get_exe_path(boosthub_path);
            strcat(boosthub_path, "/warehouse");
            // create log dir
            FILE_OPERATOR.create_dir(boosthub_path, 0777); //检测仓库文件夹如果没有则进行创建
            char filename[1024];
            std::string time_str = boosthub_time::get();
            const char *time = time_str.c_str();
            sprintf(filename, "%s/%s_%d.body", boosthub_path, time, socket);
            std::cout << "time " << time << std::endl;
            if (body)
            {
                std::ofstream outfile;
                outfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc); //输入文件的路径
                outfile.write(body, request.content_length);
                outfile.close(); //调用close（）函数关闭文件
            }
        }
        // response
        route_root(socket, request);
    }

private:
    static void route_root(int socket, http_request request)
    {
        const char *line1 = "HTTP/1.0 200\n";
        const char *line2 = "Content-Type: text/json;charset:utf-8;\n";
        const char *response_body = "{\"message\":\"hello boosthub server\"}";
        char line3[512];
        sprintf(line3, "Content-Length: %zd\n\n", strlen(response_body));
        int state = write(socket, line1, strlen(line1));
        state = write(socket, line2, strlen(line2));
        state = write(socket, line3, strlen(line3));
        state = write(socket, response_body, strlen(response_body));
    }
};
#endif
//'HTTP/1.1 404' 'Content-Type: text/html' 'Content-Length: 4413' 'Date: Fri, 29 Apr 2022 01:36:05 GMT'