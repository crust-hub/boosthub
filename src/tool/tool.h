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

//线程函数
void *socket_process_thread(void *client_socket);
//对外服务函数
int new_socket_process_thread(int client_socket);

/**
 * @brief 工具桶
 *
 */
class tool_bucket
{
private:
public:
    tool_bucket();
    ~tool_bucket();
    boost_log *BOOST_LOG;         // log工具
    arg_process *ARG_PROCESS;     // arg处理工具
    file_operator *FILE_OPERATOR; //文件操作工具
};
#endif