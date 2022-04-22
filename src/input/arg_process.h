#pragma once
#ifndef __ARG_PROCESS_H__
#define __ARG_PROCESS_H__
#include <cstdio>
#include <iostream>
#include <string.h>
#include "../net/boost_socket.h"
#include "../client/boosthub_client.h"

// arg处理
class arg_process
{
private:
    int _argc;
    char **_argv;

public:
    //状态码
    static const int DOWNLOADFILE = 0;
    static const int UPLOADFILE = 1;
    static const int ERROR = 2;
    arg_process();
    arg_process(int argc, char ***argv);
    int process();

public:
    void result_none();
};
#endif