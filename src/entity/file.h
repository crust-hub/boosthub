#pragma once
#ifndef __FILE_H__
#define __FILE_H__
#include <string>
#include <iostream>
//文件实体类
class file
{
public:
    int fd;           //文件描述符
    std::string name; //文件名称
    char type;        //文件类型 d or f

private:
    friend std::ostream &operator<<(std::ostream &os, file &item); //重写<<操作符
};
std::ostream &operator<<(std::ostream &os, file &item);
#endif