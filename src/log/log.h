#pragma once
#ifndef __LOG_H__
#define __LOG_H__
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fstream>
#include "../file/file_operator.h"
#include "../tool/boosthub_time.h"

/*feature:
Reconstruct the log class into reusable multi file oriented
*/
class boost_log
{
private:
    FILE *log_fd_;

public:
    /*Log file identifier*/
    void init();
    void check_init();
    /*print message*/
    void info(const char *message);
    /*print error*/
    void error(const char *message);
    /*print warn info*/
    void warn(const char *message);
    /*close log file*/
    void close();
    ~boost_log();
};
#endif