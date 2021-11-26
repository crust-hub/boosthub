#pragma once
#ifndef __LOG_H__
#define __LOG_H__
#include<iostream>
#include<ctime>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fstream>
#include "../file/file_operator.h"

/*feature:
Reconstruct the log class into reusable multi file oriented
*/
class boost_log{
private:
    /*Get current time*/
    static char* getTime(){
        char* back=new char[512];
        // Based on the current date / time of the current system
        time_t now = time(0);
        tm *ltm = localtime(&now);
        sprintf(back,"%d/%d/%d %d:%d:%d",
            1900 + ltm->tm_year,
            1+ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec
        );
        return back;
    }
    FILE* log_fd_;
public:
    /*Log file identifier*/
    void init();
    void check_init();
    /*print message*/
    void info(const char* message);
    /*print error*/
    void error(const char* message);
    /*print warn info*/
    void warn(const char* message);
    /*close log file*/
    void close();
};
#endif