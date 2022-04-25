#include "./boosthub_http.h"
#include <iostream>
/**
 * @brief Construct a new boosthub http::boosthub http object
 *
 */
boosthub_http::boosthub_http()
{
}

std::size_t boosthub_http::header_check(std::string &buffer)
{
    std::cout << buffer << std::endl;
    return -1;
}

//创建单例
boosthub_http boosthub_http_instance;