#include<iostream>
#include"./log/log.h"
#include"./input/arg_process.h"
#include"./file/dir_reader.h"
#include"./file/file_operator.h"
using namespace std;

/*What to do when the program closes*/
void process_end_todo();

int main(int argc,char**argv){
    boost_log::info("hello");
    boost_log::error("出现未知错误");
    boost_log::warn("警告");
    ARG_PROCESS->process();//处理arg
    //try read folder info
    char boosthub_path[512]={0};
    file_operator::get_exe_path(boosthub_path);
    file_operator::read_folder(boosthub_path);
    return 0;
}

/*What to do when the program closes*/
void process_end_todo(){
    boost_log::close();//关闭log文件流
}