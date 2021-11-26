#ifndef __TOOL_H__
#define __TOOL_H__
#include"./log/log.h"
#include"./input/arg_process.h"
#include"./file/dir_reader.h"
#include"./file/file_operator.h"
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