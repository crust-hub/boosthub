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
        // POST /
        if (request.url == "/" && request.method == "POST" && open_receive_service && request.content_length > 0)
        {
            http_handler::upload_data(socket, request);
            return true;
        }
        // GET /
        if (request.method == "GET" && (request.url == "/" || request.url == "/index.html"))
        {
            http_handler::route_root(socket, request);
            return true;
        }
        // GET /upload
        if (request.method == "GET" && (request.url == "/upload" || request.url == "/upload.html"))
        {
            http_handler::upload(socket, request);
            return true;
        }
        http_handler::res_404(socket, request);
        return true;
    }

private:
    // GET /
    static void route_root(int socket, const http_request &request)
    {
#include "./asset/index_html.h"
        page_sender(index_html, socket);
    }

    // GET /upload
    static void upload(int socket, const http_request &request)
    {
#include "./asset/upload_html.h"
        page_sender(upload_html, socket);
    }

    // POST /
    static void upload_data(int socket, const http_request &request)
    {
        std::cout << __FILE__ << " " << __LINE__ << " " << request.content_type << std::endl;
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
        sprintf(filename, "%s//%s_%d.body", boosthub_path, time, socket);
        if (body)
        {
            std::ofstream outfile;
            outfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc); //输入文件的路径
            outfile.write(body, request.content_length);
            outfile.close(); //调用close（）函数关闭文件
        }
#include "./asset/upload_html.h"
        page_sender(upload_html, socket);
    }

    // res 404
    static void res_404(int socket, const http_request &request)
    {
        std::string res_404 = "HTTP/1.0 404\n\n";
        size_t res = write(socket, res_404.c_str(), res_404.size());
    }

private:
    static void page_sender(const char *html, int socket)
    {
        std::vector<const char *> headers;
        headers.push_back("HTTP/1.0 200\n");
        headers.push_back("Content-Type: text/html;charset:utf-8;\n");
        char line3[512];
        sprintf(line3, "Content-Length: %zd\n\n", strlen(html));
        headers.push_back(line3);
        for (auto header_str : headers)
        {
            size_t res = write(socket, header_str, strlen(header_str));
        }
        size_t res = write(socket, html, strlen(html));
    }
};
#endif