#include "./boosthub_buffer.h"

boosthub_buffer::boosthub_buffer()
{
    this->buffer = nullptr;
    this->size = 0;
    this->buffer = (char *)malloc(sizeof(char) * 512);
    if (buffer != nullptr)
    {
        this->size = 512;
        this->length = 0;
    }
}

boosthub_buffer::~boosthub_buffer()
{
    if (this->buffer)
    {
        free(this->buffer);
    }
}

std::size_t boosthub_buffer::get_size()
{
    return this->size;
}

std::size_t boosthub_buffer::get_length()
{
    return this->length;
}

bool boosthub_buffer::push_back(const char *source, std::size_t len)
{
    bool result = false;
    if (source == nullptr || len <= 0 || this->buffer == nullptr)
    {
        return result;
    }
    //拷贝source中的前len个byte追加到this->buffer后面
    //需要检测this->buffer空间是否足够
    if (this->size < this->length + len)
    {
        //重新申请分配内存
        this->buffer = (char *)realloc(this->buffer, sizeof(char) * (this->length + len) * 2);
        if (this->buffer)
        {
            this->size = (this->length + len) * 2;
            //拷贝source
            char *ptr = (char *)memcpy((this->buffer + this->length), source, len);
            if (ptr)
            {
                this->length += len;
            }
            result = true;
        }
        else
        {
            this->size = 0;
            this->length = 0;
        }
    }
    else
    {
        //拷贝source
        char *ptr = (char *)memcpy((this->buffer + this->length), source, len);
        if (ptr)
        {
            this->length += len;
        }
        result = true;
    }
    return result;
}

void boosthub_buffer::clear()
{
    if (this->buffer)
    {
        free(this->buffer);
        this->size = 0;
        this->length = 0;
    }
}