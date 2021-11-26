#ifndef __TOOL_H__
#define __TOOL_H__
#include"./file/file_operator.h"
#include"./log/log.h"
#include"./input/arg_process.h"
#include"./file/dir_reader.h"
#include"./entity/file.h"
#include"./entity/folder.h" 
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