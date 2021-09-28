#include"UserInputProcess/ArgcArgvProcess.h"

ArgcArgvProcess::ArgcArgvProcess(){
    _argc=0;
    _argv=nullptr;
}

ArgcArgvProcess::ArgcArgvProcess(int argc,char*** argv){
    _argc=argc;
    _argv=*(argv);
}

int ArgcArgvProcess::process(){
    if(_argc==0||_argv==nullptr){
        return this->ERROR;
    }
    for(int i=0;i<_argc;i++){
        printf("%s\n",_argv[i]);
    }
    return this->DOWNLOADFILE;
}