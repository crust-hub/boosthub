#ifndef __ARG_PROCESS_H__
#define __ARG_PROCESS_H__
#include<cstdio>
class arg_process{
private:
    int _argc;
    char** _argv;
public:
    static const int DOWNLOADFILE=0;
    static const int UPLOADFILE=1;
    static const int ERROR=2;
    arg_process();
    arg_process(int argc,char*** argv);
    int process();
};
//用户输入处理
extern  arg_process*  BOOST_ARG_PROCESS;
#endif