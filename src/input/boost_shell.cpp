#include"boost_shell.h"
#include<iostream>
#include <stdio.h>
#include <stdlib.h>

boost_shell::boost_shell(){
    this->USER.set_socket_fd(-1);
}

boost_shell::boost_shell(int socket_fd){
    this->USER.set_socket_fd(socket_fd);
}

void boost_shell::run(std::string shell){
    if(this->USER.get_socket_fd()==-1){
        return;
    }
    /*对命令行进行解析*/
    if(shell.size()>0){
        patch(shell);
    }
}

void boost_shell::set_socket_fd(int socket_fd){
    this->USER.set_socket_fd(socket_fd);
}

void boost_shell::patch(std::string&shell){
    /*命令行模式匹配*/
    if(shell=="ls"){
        ls();
    }
}


void boost_shell::ls(){
    /*发送根目录信息*/
    char boosthub_path[512]={0};
    FILE_TOOL.get_exe_path(boosthub_path);
    //根据用户所在位置获得文件夹信息
    folder finded_folder=FILE_TOOL.read_folder(this->USER.get_now_path().c_str());
    std::vector<file> files=finded_folder.get_list();
    char buffer[512]={0};

    int socket_fd=this->USER.get_socket_fd();//获得用户套接字    
    /*头部信息*/
    sprintf(buffer,"\nFolder Path: %s File Sum: %ld \n\0",finded_folder.path.c_str(),files.size());
    write(socket_fd,buffer,strlen(buffer));
    sprintf(buffer,"\n%-16s\t%-16s\t%-16s\n\0","Fd","Name","Type");
    write(socket_fd,buffer,strlen(buffer));

    /*目录遍历*/
    for(int i=0;i<files.size();i++){
        sprintf(buffer,"%-16d\t%-16s\t%-16c\n\0",files[i].fd,files[i].name.c_str(),files[i].type);
        write(socket_fd,buffer,strlen(buffer));
    }
    write(socket_fd,">>",strlen(">>"));
}