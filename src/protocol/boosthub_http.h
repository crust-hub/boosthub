#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sys/socket.h>
#include <cstring>
#include "../tool/boosthub_buffer.h"

/**
 * @brief boosthub http protocol
 *
 */
class boosthub_http
{
public:
    boosthub_http();

    /**
     *
     * @brief 检测http请求报文头部是否接受完毕,当缓存超过一定长度后后清理缓存
     *
     * @param boosthub_buffer &buffer socket接收内容缓存
     * @param max_length 最大缓存长度,当超过max_length时会将buffer清理
     * @return std::size_t 报文头部大小 为零0则没有找到合法头部
     */
    std::size_t header_check(boosthub_buffer &buffer, std::size_t max_length);

    /**
     * @brief HTTP 头部分析
     *
     * @param buffer 接收缓冲
     * @param header_end_index header结束标志\r\n\r\n 第一个\r的下标
     */
    std::map<std::string, std::string> header_analysis(boosthub_buffer &buffer, std::size_t header_end_index);

    /**
     * @brief 从套接字socket中判断body大小
     *
     * @param socket socket文件标识符
     * @param http_header http头部信息
     * @return std::size_t content-length大小
     */
    std::size_t read_body(int socket, std::map<std::string, std::string> http_header);

    /**
     * @brief 将字符串根据指定字符进行split
     *
     * @param str 要处理的字符串
     * @param ch 根据ch进行split
     * @param count 只处理前count个ch，当count为0时处理所有ch
     * @return std::vector<std::string>
     */
    static std::vector<std::string> string_split(std::string &str, const char ch, const std::size_t count);

    /**
     * @brief 根据key查找是否有响应的key
     *
     * @param header http头部
     * @param key 要找的key
     * @return std::string 如果有则返回响应value否则返回空串
     */
    static std::string map_has_key(std::map<std::string, std::string> &header, std::string key);
};
