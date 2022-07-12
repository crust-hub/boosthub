#ifndef __BOOSTHUB_BUFFER__
#define __BOOSTHUB_BUFFER__
#include <iostream>
#include <cstdlib>
#include <cstring>

//暂时未设计外存存储机制，直接存放到内存，使得不能接收很大的内容
//应该开发一种超过一定大小后缓存到外存（设计临时文件）的机制
//向外部提供获取内容的接口
class boosthub_buffer
{
public:
    char *buffer;
    std::size_t get_size();
    std::size_t get_length();
    boosthub_buffer();
    bool push_back(const char *source, std::size_t len);
    ~boosthub_buffer();
    void clear();

private:
    std::size_t size;
    std::size_t length;
};
#endif