#ifndef __TOOL_H__
#define __TOOL_H__
#include"../file/file_operator.h"
#include"../log/log.h"
#include"../input/arg_process.h"
#include"../file/dir_reader.h"
#include"../entity/file.h"
#include"../entity/folder.h" 
#include"../net/boost_socket.h"
#include <pthread.h>

void* socket_process_thread(void*client_socket);
int new_socket_process_thread(int client_socket);
class tool_bucket{
private:
    
public:
    tool_bucket();
    ~tool_bucket();
    boost_log* BOOST_LOG;
    arg_process* ARG_PROCESS;
    file_operator* FILE_OPERATOR;
};
#endif