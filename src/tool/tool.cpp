#include"tool.h"
tool_bucket::tool_bucket(){
    BOOST_LOG=new boost_log();
    ARG_PROCESS=new arg_process();
    FILE_OPERATOR=new file_operator();
}
tool_bucket::~tool_bucket(){
    delete BOOST_LOG;
    delete ARG_PROCESS;
    delete FILE_OPERATOR;
}