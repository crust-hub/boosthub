#ifndef __FILE_H__
#define __FILE_H__
#include <string>
#include <iostream>
class file{
public:
    int fd;
    std::string name;
    char type;
private:
    friend std::ostream &operator<<(std::ostream &os, file &item);
};
std::ostream &operator<<(std::ostream &os, file &item);
#endif