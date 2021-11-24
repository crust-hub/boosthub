#include<iostream>
#include"./log/log.h"
#include"./input/arg_process.h"
using namespace std;
int main(int argc,char**argv){
    BOOST_LOG->info("hello");
    BOOST_LOG->error("出现未知错误");
    BOOST_LOG->warn("警告");
    int back=BOOST_ARG_PROCESS->process();
    cout<<"backcode "<<back<<endl;
    BOOST_LOG->close();//关闭log文件流
    delete BOOST_ARG_PROCESS;
    delete BOOST_LOG;
    return 0;
}