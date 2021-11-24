#include"arg_process.h"

arg_process::arg_process(){
    _argc=0;
    _argv=nullptr;
}

arg_process::arg_process(int argc,char*** argv){
    _argc=argc;
    _argv=*(argv);
}

int arg_process::process(){
    if(_argc==0||_argv==nullptr){
        return this->ERROR;
    }
    for(int i=0;i<_argc;i++){
        printf("%s\n",_argv[i]);
    }
    return this->DOWNLOADFILE;
}

arg_process*  ARG_PROCESS=new arg_process();