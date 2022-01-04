#pragma once
#ifndef __DIR_READER_H__
#define __DIR_READER_H__
#include <iostream>
#include <string>

//问价夹读取器
class dir_reader
{
private:
    std::string URI_; //资源定位符
public:
    dir_reader();
    dir_reader(std::string URI);

public:
    std::string get_URI();
};
#endif