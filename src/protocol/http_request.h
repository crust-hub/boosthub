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
    std::size_t content_length;
    std::map<std::string, std::string> header;
    char *request_body;
};
#endif