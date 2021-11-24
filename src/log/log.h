#ifndef __LOG_H__
#define __LOG_H__
#include<iostream>
#include<ctime>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fstream>

class boost_log{
private:
    /*获得当前时间*/
    static char* getTime(){
        char* back=new char[512];
        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        tm *ltm = localtime(&now);
        sprintf(back,"%d年%d月%d日 %d:%d:%d",
            1900 + ltm->tm_year,
            1+ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec
        );
        return back;
    }
    static void  create_file(char *filename){ 
        if(creat(filename,0755)<0){ 
            printf("create file %s failure!\n",filename); 
            exit(EXIT_FAILURE); 
        }else{ 
            printf("create file %s success!\n",filename); 
        } 
    }
public:
    /*log文件标识符*/
    static FILE* log_fd_;
    static void init(){
        /*初始化生成./log/boost.log文件 如果存在则不做处理 直接打开文件*/
        char * time=getTime();
        std::cout<<"[Log::warn]["<<time<<"] "<<"log/boost.log文件不存在"<<std::endl;
        log_fd_=fopen("./boost.log","a");
        if(NULL==log_fd_){
            std::cout<<"[Log::warn]["<<time<<"] "<<"log/boost.log创建失败"<<std::endl;
        }else{
            std::cout<<"[Log::info]["<<time<<"] "<<"log/boost.log就绪"<<std::endl;
        }
    }
    static void check_init(){
        if(NULL==log_fd_){//log文件没有打开成功则retry
            init();
        }
    }
    /*打印信息*/
    static void info(const char* message){
        check_init();
        char * time=getTime();
        std::cout<<"[Log::info]["<<time<<"] "<<message<<std::endl;
        fprintf( log_fd_,"[Log::info][%s] %s\n",time,message);
        delete time;
    }
    /*打印错误*/
    static void error(const char* message){
        check_init();
        char * time=getTime();
        std::cout<<"[Log::error]["<<time<<"] "<<message<<std::endl;
        fprintf( log_fd_,"[Log::error][%s] %s\n",time,message);
        delete time;
    }
    /*打印警告信息*/
    static void warn(const char* message){
        check_init();
        char * time=getTime();
        std::cout<<"[Log::warn]["<<time<<"] "<<message<<std::endl;
        fprintf( log_fd_,"[Log::warn][%s] %s\n",time,message);
        delete time;
    }
    /*关闭log文件流*/
    static void close(){
        if(log_fd_!=NULL){
            fclose(log_fd_);
        }
        log_fd_=NULL;
    }
};
//log工具单例
extern  boost_log*  BOOST_LOG;
#endif