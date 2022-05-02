#ifndef __BOOSTHUB_TIME_H__
#define __BOOSTHUB_TIME_H__
#include <ctime>
#include <string>
#include <iostream>
class boosthub_time
{
public:
    static std::string get()
    {
        char *back = new char[512];
        // Based on the current date / time of the current system
        time_t now = time(0);
        tm *ltm = localtime(&now);
        sprintf(back, "%d-%d-%d-%d:%d:%d",
                1900 + ltm->tm_year,
                1 + ltm->tm_mon,
                ltm->tm_mday,
                ltm->tm_hour,
                ltm->tm_min,
                ltm->tm_sec);
        std::string result = std::string(back);
        delete back;
        return result;
    }
};
#endif