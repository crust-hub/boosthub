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
#include "../file/file_operator.h"


/*feature:
Reconstruct the log class into reusable multi file oriented
*/
class boost_log{
private:
    /*Get current time*/
    static char* getTime(){
        char* back=new char[512];
        // Based on the current date / time of the current system
        time_t now = time(0);
        tm *ltm = localtime(&now);
        sprintf(back,"%d/%d/%d %d:%d:%d",
            1900 + ltm->tm_year,
            1+ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec
        );
        return back;
    }
public:
    /*Log file identifier*/
    static FILE* log_fd_;
    static void init(){
        /*Initialize the generated log / boost.log file. If it exists,
         open the file directly without processing*/
        /*Get the absolute path of the boothub*/
        char boosthub_path[512]={0};
        file_operator::get_exe_path(boosthub_path);
        strcat(boosthub_path,"/boostHubLogs");//log folder absolute path
        printf("Log folder absolute path: %s\n",boosthub_path);
        //create log dir
        file_operator::create_dir(boosthub_path,0777);
        strcat(boosthub_path,"/boost.log");//boost.log absolute path
        file_operator::create_new_file(boosthub_path,0777);
        printf("Boost.log absolute path: %s\n",boosthub_path);
        char * time=getTime();
        std::cout<<"[Log::warn]["<<time<<"] "<<"not founded boost.log"<<std::endl;
        log_fd_=fopen(boosthub_path,"a+");
        if(NULL==log_fd_){
            std::cout<<"[Log::warn]["<<time<<"] "<<"create boost.log filed"<<std::endl;
        }else{
            std::cout<<"[Log::info]["<<time<<"] "<<"boost.log ok,we get start"<<std::endl;
        }
    }
    static void check_init(){
        if(NULL==log_fd_){//If the log file is not opened successfully, retry
            init();
        }
    }
    /*print message*/
    static void info(const char* message){
        check_init();
        char * time=getTime();
        std::cout<<"[Log::info]["<<time<<"] "<<message<<std::endl;
        fprintf( log_fd_,"[Log::info][%s] %s\n",time,message);
        delete time;
    }
    /*print error*/
    static void error(const char* message){
        check_init();
        char * time=getTime();
        std::cout<<"[Log::error]["<<time<<"] "<<message<<std::endl;
        fprintf( log_fd_,"[Log::error][%s] %s\n",time,message);
        delete time;
    }
    /*print warn info*/
    static void warn(const char* message){
        check_init();
        char * time=getTime();
        std::cout<<"[Log::warn]["<<time<<"] "<<message<<std::endl;
        fprintf( log_fd_,"[Log::warn][%s] %s\n",time,message);
        delete time;
    }
    /*close log file*/
    static void close(){
        if(log_fd_!=NULL){
            fclose(log_fd_);
        }
        log_fd_=NULL;
    }
};
/*init log fd*/
FILE* boost_log::log_fd_=NULL;
#endif