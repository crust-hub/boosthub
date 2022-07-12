#ifndef __HTTP_REQUEST__
#define __HTTP_REQUEST__
#include <string>
#include <map>
#include <iostream>
class http_request
{
public:
    http_request(std::map<std::string, std::string> header);
    void print();
    std::string method;
    std::string url;
    std::string version;
    std::string content_type;
    std::size_t content_length;
    std::map<std::string, std::string> header;
    char *request_body;

private:
    //构造函数传进来的只是http头部根据\n进行split的并没有考虑\r所以要修剪
    static std::string &string_trim(std::string &s)
    {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        //如果最后一位字符为'\r'则删除
        if (s.size() > 0 && s.c_str()[s.size() - 1] == '\r')
        {
            s.erase(s.size() - 1);
        }
        return s;
    }
};
#endif