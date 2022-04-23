#pragma once
#ifndef __TOOL_H__
#define __TOOL_H__
#include "../file/file_operator.h"
#include "../log/log.h"
#include "../input/arg_process.h"
#include "../file/dir_reader.h"
#include "../entity/file.h"
#include "../entity/folder.h"
#include "../net/boost_socket.h"
#include "../input/boost_shell.h"
#include <pthread.h>

/**
 * @brief 工具桶 单例
 *
 */
class tool_bucket
{
public:
    static bool exist;

private:
    static tool_bucket instance;

public:
    tool_bucket();
    ~tool_bucket();
    boost_log *BOOST_LOG;         // log工具
    arg_process *ARG_PROCESS;     // arg处理工具
    file_operator *FILE_OPERATOR; //文件操作工具
};
#endif