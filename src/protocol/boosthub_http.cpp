#include "./boosthub_http.h"
/**
 * @brief Construct a new boosthub http::boosthub http object
 *
 */
boosthub_http::boosthub_http()
{
}

std::size_t boosthub_http::header_check(std::string &buffer, std::size_t max_length)
{
    //探测HTTP头部是否可以获取检测\r\n\r\n
    std::size_t header_end_index = 0;
    for (std::size_t i = 0; i < buffer.size(); i++)
    {
        if (i < buffer.size() - 3)
        {
            if (buffer[i] == '\r' && buffer[i + 1] == '\n' && buffer[i + 2] == '\r' && buffer[i + 3] == '\n')
            {
                header_end_index = i;
                break;
            }
        }
        else if (i < buffer.size() - 1)
        {
            if (buffer[i] == '\n' && buffer[i + 1] == '\n')
            {
                header_end_index = i;
                break;
            }
        }
        else
        {
            break;
        }
    }
    //限制HTTP头部缓冲大小
    if (header_end_index == 0 && buffer.size() > max_length)
    {
        buffer = ""; //清空buffer
    }
    return header_end_index;
}

std::map<std::string, std::string> boosthub_http::header_analysis(std::string &buffer, std::size_t header_end_index)
{
    std::map<std::string, std::string> header_content;
    if (header_end_index <= 0)
    {
        return header_content;
    }
    //截取头部部分
    std::string header = buffer.substr(0, header_end_index + 1);
    std::cout << header << std::endl;
    //分离\n
    std::vector<std::string> rows = boosthub_http::string_split(header, '\n', 0);
    if (rows.size() == 0)
    {
        return header_content;
    }
    //检测第一行
    std::vector<std::string> header_first_row = boosthub_http::string_split(rows[0], ' ', 0);
    if (header_first_row.size() != 3)
    {
        return header_content;
    }
    // HTTP METHOD CHECK
    if (header_first_row[0] != "POST" && header_first_row[0] != "GET")
    {
        return header_content;
    }
    // HTTP VERSION CHECK
    if (header_first_row[2] != "HTTP/1.1" && header_first_row[2] != "HTTP/1.0")
    {
        return header_content;
    }
    //取得Method URL Version 头部信息
    header_content.insert(std::pair<std::string, std::string>(std::string("Method"), header_first_row[0]));
    header_content.insert(std::pair<std::string, std::string>(std::string("URL"), header_first_row[1]));
    header_content.insert(std::pair<std::string, std::string>(std::string("Version"), header_first_row[2]));
    //分析头部的其他行
    for (std::size_t row_index = 1; row_index < rows.size(); row_index++)
    {
        std::vector<std::string> header_row_splited = boosthub_http::string_split(rows[row_index], ':', 1);
        if (header_row_splited.size() == 2)
        {
            header_content.insert(std::pair<std::string, std::string>(header_row_splited[0], header_row_splited[1]));
        }
    }
    //将buffer中的http头部部分清理掉
    if (buffer[header_end_index] == '\n' && buffer[header_end_index + 1] == '\n')
    {
        buffer = buffer.substr(header_end_index + 2, (buffer.size() - 1) - (header_end_index + 2) + 1);
    }
    else
    {
        buffer = buffer.substr(header_end_index + 4, (buffer.size() - 1) - (header_end_index + 4) + 1);
    }
    // std::cout << "clean part of header content" << std::endl;
    // std::cout << buffer << std::endl;
    return header_content;
}

std::string boosthub_http::read_body(int socket, std::map<std::string, std::string> http_header, std::string &out_buffer)
{
    std::string buffer = out_buffer;
    out_buffer = std::string("");
    std::string method = boosthub_http::map_has_key(http_header, std::string("Method"));
    std::string content_type = boosthub_http::map_has_key(http_header, std::string("Content-Type"));
    std::string content_length_str = boosthub_http::map_has_key(http_header, std::string("Content-Length"));
    if (method == "" || content_type == "" || content_length_str == "")
    {
        return buffer;
    }
    auto content_length = std::stoull(content_length_str);
    // std::cout << "Method " << method << std::endl;
    // std::cout << "Content-Type " << content_type << std::endl;
    // std::cout << "Content-Length " << content_length << std::endl;
    // std::cout << "准备接收请求体部分" << std::endl;
    if (buffer.size() >= content_length)
    {
        return buffer;
    }
    char char_buffer[512];
    std::size_t read_len = 0;
    //接收剩余请求体部分
    while (1)
    {
        read_len = recv(socket, char_buffer, sizeof(char_buffer) - 1, 0);
        std::cout << "read_len " << read_len << " content-length " << content_length << " buffer_size " << strlen(buffer.c_str()) << std::endl;
        if (read_len <= 0)
        {
            break;
        }
        buffer += std::string(char_buffer);
        if (buffer.size() >= content_length || buffer.size() > 8 * 1024) //请求体大小限制
        {
            break;
        }
    }
    return buffer;
}

//创建单例
boosthub_http boosthub_http_instance;