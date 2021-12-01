#include "boost_shell.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

boost_shell::boost_shell()
{
    this->USER.set_socket_fd(-1);
}

boost_shell::boost_shell(int socket_fd)
{
    this->USER.set_socket_fd(socket_fd);
}

void boost_shell::run(std::string shell)
{
    if (this->USER.get_socket_fd() == -1)
    {
        return;
    }
    /*对命令行进行解析*/
    if (shell.size() > 0)
    {
        patch(shell);
    }
}

void boost_shell::set_socket_fd(int socket_fd)
{
    this->USER.set_socket_fd(socket_fd);
}

void boost_shell::patch(std::string &shell)
{
    std::vector<std::string> words=word_split(shell);
    /*命令行模式匹配*/
    if (check_ls(words))
    {
        ls();
    }else if(check_cd(words)){
        /*执行cd逻辑判断 获取要cd的绝对路径*/
        std::string concat_path=this->USER.get_now_path()+"/"+words[1];
        if(words[1][0]=='/'){//用户输入绝对路径
            concat_path=words[1];
        }
        char* real_new_path=realpath(concat_path.c_str(),NULL);
        std::cout<<"拼接后的路径 "<<concat_path<<std::endl;
        std::string new_path=std::string("/");
        if(real_new_path!=NULL){
            new_path=std::string(real_new_path);//新路径
            delete real_new_path;
            real_new_path=NULL;
        }
        //检查是否为根路径
        //检查是否返回上级(涉及到多级问题，可能要先进行获取DIR然后文件夹存在 则使用文件夹的真实绝对路径)
        std::cout<<"cd命令 新路径为: "<<new_path<<std::endl;
        //检查文件夹是否存在
        if(FILE_TOOL.check_folder_path_real(new_path.c_str())){
            this->USER.set_nowpath(new_path);
            std::cout<<"文件夹存在\n";
            this->cd();
        }else{
            std::cout<<"文件夹不存在\n";
        }
    }else if(check_pwd(words)){

    }else{
        send_illegal();//告诉用户它的指令是非法的
    }
}

void boost_shell::ls()
{
    /*发送根目录信息*/
    char boosthub_path[512] = {0};
    FILE_TOOL.get_exe_path(boosthub_path);
    //根据用户所在位置获得文件夹信息
    folder finded_folder = FILE_TOOL.read_folder(this->USER.get_now_path().c_str());
    std::vector<file> files = finded_folder.get_list();
    char buffer[512] = {0};
    int socket_fd = this->USER.get_socket_fd(); //获得用户套接字
    /*头部信息*/
    sprintf(buffer, "\nNow Path: %s     This Path Inner Sum: %ld \n\0", finded_folder.path.c_str(), files.size());
    write(socket_fd, buffer, strlen(buffer));
    sprintf(buffer, "\n%-16s\t%-16s\t%-16s\n\0", "Fd", "Name", "Type");
    write(socket_fd, buffer, strlen(buffer));

    /*目录遍历*/
    for (int i = 0; i < files.size(); i++)
    {
        sprintf(buffer, "%-16d\t%-16s\t%-16c\n\0", files[i].fd, files[i].name.c_str(), files[i].type);
        write(socket_fd, buffer, strlen(buffer));
    }
    write(socket_fd, ">>", strlen(">>"));
}

/*cd命令*/
void boost_shell::cd(){
    char buffer[512] = {0};
    int socket_fd = this->USER.get_socket_fd(); //获得用户套接字
    /*头部信息*/
    sprintf(buffer, "\nNow Path: %s  \n\0", this->USER.get_now_path().c_str());
    write(socket_fd, buffer, strlen(buffer));
}


//检查是否为cd命令
bool boost_shell::check_cd(std::vector<std::string>& words)
{
    if(2!=words.size()){
        return false;
    }
    if(words[0]!="cd"){
        return false;
    }
    //check path
    return true;
}

//检查是否为ls命令
bool boost_shell::check_ls(std::vector<std::string>& words)
{
    return 1==words.size()&&words[0]=="ls";
}

std::string &boost_shell::string_trim(std::string &s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

//分割字符串并将其如"cd /fdcd/edw/gbf" => string[]={"cd","/fd/edw/gbf"}
std::vector<std::string> boost_shell::word_split(std::string&s){
    s=string_trim(s);
    std::vector<std::string> result;
    if(s.empty()){
        return result;
    }
    //split by " "
    std::string word="";
    for(long i=0;i<s.size();i++){
        if(word==""&&s[i]==' '){
            continue;
        }
        if(word!=""&&s[i]==' '){
            result.push_back(word);
            word="";
            continue;
        }
        if(word!=""&&i==s.size()-1){
            word=word+s[i];
            result.push_back(word);
            continue;
        }
        word=word+s[i];
    }
/*
    for(long i=0;i<result.size();i++){
        std::cout<<"word"<<i<<" :"<<result[i]<<std::endl; 
    }*/
    return result;
}

//检查是否为pwd命令
bool boost_shell::check_pwd(std::vector<std::string>& words){
    if(words.empty()){
        return false;
    }
    if(words.size()!=1){
        return false;
    }
    if(words[0]=="pwd"){
        char buffer[512] = {0};
        int socket_fd = this->USER.get_socket_fd(); //获得用户套接字
        /*头部信息*/
        sprintf(buffer, "\nNow Path: %s  \n\0", this->USER.get_now_path().c_str());
        write(socket_fd, buffer, strlen(buffer));
        return true;
    }
    return false;
}

//send "Illegal command. Please check your input information"
void boost_shell::send_illegal(){
    int socket_fd = this->USER.get_socket_fd(); //获得用户套接字
    const char* message="Illegal command. Please check your input information\n\0";
    write(socket_fd,message, strlen(message));
}