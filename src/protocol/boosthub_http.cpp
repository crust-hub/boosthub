#include "./boosthub_http.h"
#include "../tool/tool_bucket.h"

extern tool_bucket boosthub_tool_bucket;

/**
 * @brief Construct a new boosthub http::boosthub http object
 *
 */
boosthub_http::boosthub_http()
{
}

std::size_t boosthub_http::header_check(boosthub_buffer &buffer, std::size_t max_length)
{
    //探测HTTP头部是否可以获取检测\r\n\r\n
    std::size_t header_end_index = 0;
    for (std::size_t i = 0; i < buffer.get_length(); i++)
    {
        if (i < buffer.get_length() - 3)
        {
            if (buffer.buffer[i] == '\r' && buffer.buffer[i + 1] == '\n' && buffer.buffer[i + 2] == '\r' && buffer.buffer[i + 3] == '\n')
            {
                header_end_index = i + 4;
                break;
            }
        }
        else if (i < buffer.get_size() - 1)
        {
            if (buffer.buffer[i] == '\n' && buffer.buffer[i + 1] == '\n')
            {
                header_end_index = i + 2;
                break;
            }
        }
        else
        {
            break;
        }
    }
    //限制HTTP头部缓冲大小
    if (header_end_index == 0 && max_length != 0 && buffer.get_length() > max_length)
    {
        buffer.clear(); //清空buffer
    }
    return header_end_index;
}

std::map<std::string, std::string> boosthub_http::header_analysis(boosthub_buffer &buffer, std::size_t header_end_index)
{
    std::map<std::string, std::string> header_content;
    if (header_end_index <= 0)
    {
        return header_content;
    }
    //截取头部部分
    std::string header = std::string(buffer.buffer, buffer.buffer + header_end_index);
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
    return header_content;
}

std::size_t boosthub_http::read_body(int socket, std::map<std::string, std::string> http_header)
{
    std::string method = boosthub_http::map_has_key(http_header, std::string("Method"));
    std::string content_type = boosthub_http::map_has_key(http_header, std::string("Content-Type"));
    std::string content_length_str = boosthub_http::map_has_key(http_header, std::string("Content-Length"));
    std::string transfer_encoding = boosthub_http::map_has_key(http_header, std::string("Transfer-Encoding"));
    if (method == "" || content_type == "" || content_length_str == "")
    {
        return 0;
    }
    auto content_length = std::stoull(content_length_str);
    return content_length;
}

std::vector<std::string> boosthub_http::string_split(std::string &str, const char ch, const std::size_t count)
{
    std::vector<std::string> result;
    std::size_t last_index = 0;
    std::size_t index = 0;
    std::size_t process_count = 0;
    //探测字符串
    for (auto now_ch : str)
    {
        if (count != 0 && process_count == count) //处理了count后，则直接将后面的处理掉
        {
            result.push_back(str.substr(last_index, str.size() - last_index));
            return result;
        }
        if (now_ch == ch || index == str.size() - 1)
        {
            result.push_back(str.substr(last_index, index - last_index));
            last_index = index + 1;
            process_count++;
        }
        ++index;
    }
    return result;
}

std::string boosthub_http::map_has_key(std::map<std::string, std::string> &header, std::string key)
{
    auto l_it = header.end();
    l_it = header.find(key);
    if (l_it == header.end())
        return std::string("");
    else
        return l_it->second; //返回value
}

//创建单例
boosthub_http boosthub_http_instance;