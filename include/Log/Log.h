#ifndef __LOG_H__
#define __LOG_H__
#include<iostream>
#include<ctime>
class Log{
private:
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
public:
    static void info(const char* message){
        char * time=getTime();
        std::cout<<"[Log::info]["<<time<<"] "<<message<<std::endl;
        delete time;
    }
    static void error(const char* message){
        char * time=getTime();
        std::cout<<"[Log::error]["<<time<<"] "<<message<<std::endl;
        delete time;
    }
    static void warn(const char* message){
        char * time=getTime();
        std::cout<<"[Log::warn]["<<time<<"] "<<message<<std::endl;
        delete time;
    }
};
#endif