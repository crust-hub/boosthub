#include<iostream>
#include"FileControll/kk.h"
#include"Log/Log.h"
#include"UserInputProcess/ArgcArgvProcess.h"
using namespace std;
extern Log FileHubLog;
int main(int argc,char**argv){
    FileHubLog.info("hello");
    FileHubLog.error("出现未知错误");
    FileHubLog.warn("警告");
    ArgcArgvProcess* argcArgvProcess=new ArgcArgvProcess();
    int back=argcArgvProcess->process();
    cout<<"backcode "<<back<<endl;
    delete argcArgvProcess;
    return 0;
}