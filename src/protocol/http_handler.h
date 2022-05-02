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
#include "../tool/tool_bucket.h"

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
    static bool handle(int socket, http_request request)
    {
        extern tool_bucket boosthub_tool_bucket; //引用日志实例
        constexpr bool open_receive_service = true;
        if (request.url == "/" && request.method == "POST" && open_receive_service && request.content_length > 0)
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
            if (body)
            {
                boosthub_tool_bucket.BOOST_LOG->info("create new http body file");
                std::ofstream outfile;
                outfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc); //输入文件的路径
                outfile.write(body, request.content_length);
                outfile.close(); //调用close（）函数关闭文件
                return true;
            }
        }
        // response
        if (request.method == "GET" && (request.url == "/" || request.url == "/index.html"))
        {
            route_root(socket, request);
            return true;
        }
        return false;
    }

private:
    static void route_root(int socket, http_request request)
    {
        std::vector<const char *> headers;
        headers.push_back("HTTP/1.0 200\n");
        headers.push_back("Content-Type: text/html;charset:utf-8;\n");
        const char *response_body =
            "<!DOCTYPE html>\
            <html lang =\"en\">\
                <head>\
                    <meta charset = \"UTF-8\">\
                    <title> boosthub </title>\
                    <style>\
                        *{\
                            color:#fafafa;\
                            border:0px;\
                            margin:0px;\
                            padding:0px;\
                         }\
                         header,footer{\
                            padding:1rem;\
                            height:5rem;\
                            display:flex;\
                            justify-content:flex-start;\
                            align-items:center;\
                            background-color:#1d1d1f;\
                         }\
                         main{\
                            min-height:calc(100vh - 14rem);\
                            display:flex;\
                            justify-content:center;\
                            align-items:center;\
                            background-color:#1d1d1f;\
                         }\
                    </style>\
                </head>\
                <body>\
                    <header>\
                        <span>Boosthub</span>\
                    </header>\
                    <main>\
                        <h1>Hi , get <a href=\"https://github.com/gaowanlu/boosthub\">boosthub</a> now.</h1>\
                    </main>\
                    <footer>\
                        <span>2022 design by <a href=\"https://github.com/gaowanlu\">@wanlu</a></span>\
                    </footer>\
                </body>\
            </html>";
        char line3[512];
        sprintf(line3, "Content-Length: %zd\n\n", strlen(response_body));
        headers.push_back(line3);
        for (auto header_str : headers)
        {
            write(socket, header_str, strlen(header_str));
        }
        write(socket, response_body, strlen(response_body));
    }
};
#endif
//'HTTP/1.1 404' 'Content-Type: text/html' 'Content-Length: 4413' 'Date: Fri, 29 Apr 2022 01:36:05 GMT'