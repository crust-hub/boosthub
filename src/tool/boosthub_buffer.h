#ifndef __BOOSTHUB_BUFFER__
#define __BOOSTHUB_BUFFER__
#include <iostream>
#include <cstdlib>
#include <cstring>
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