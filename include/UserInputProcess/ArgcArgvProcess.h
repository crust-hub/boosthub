#ifndef __ARGCARGVPROCESS_H__
#define __ARGCARGVPROCESS_H__
#include<cstdio>
class ArgcArgvProcess{
private:
    int _argc;
    char** _argv;
public:
    static const int DOWNLOADFILE=0;
    static const int UPLOADFILE=1;
    static const int ERROR=2;
    ArgcArgvProcess();
    ArgcArgvProcess(int argc,char*** argv);
    int process();
};
#endif