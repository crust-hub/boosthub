#pragma once
#ifndef __DIR_READER_H__
#define __DIR_READER_H__
#include <iostream>
#include <string>
/*Folder reader*/
class dir_reader{
private:
    std::string URI_;
public:
    dir_reader();
    dir_reader(std::string URI);
public:
    std::string get_URI();
};
#endif