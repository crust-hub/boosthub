#include<iostream>
#include"./tool/tool.h"
using namespace std;
/*tool bucket*/
tool_bucket* TOOL=new tool_bucket();
int main(int argc,char**argv){
    TOOL->BOOST_LOG->info("hello");
    TOOL->BOOST_LOG->error("出现未知错误");
    TOOL->BOOST_LOG->warn("警告");
    TOOL->ARG_PROCESS->process();//处理arg
    //try read folder info
    char boosthub_path[512]={0};
    TOOL->FILE_OPERATOR->get_exe_path(boosthub_path);
    vector<file> files=TOOL->FILE_OPERATOR->read_folder(boosthub_path);
    std::cout<<"Path: "<<boosthub_path<<" File Sum: "<<files.size()<<std::endl;
    for(int i=0;i<files.size();i++){
        std::cout<<files[i]<<std::endl;
    }
    delete TOOL;
    return 0;
}