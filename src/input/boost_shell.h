#pragma once
#ifndef __BOOST_SHELL__
#define __BOOST_SHELL__
#include<string>
#include"../file/file_operator.h"
#include"../log/log.h"
#include"../entity/file.h"
#include"../entity/user.h"
class tool_bucket;
class boost_shell{
private:
    std::string shell;
    file_operator FILE_TOOL;
    boost_log LOG_TOOL;
    user USER; //用户角色
public:
    boost_shell();
    boost_shell(int socket_fd);
    void run(std::string shell);
    void set_socket_fd(int socket_fd);
    void patch(std::string&shell);
    void cd(std::vector<std::string> &words);
    bool check_cd(std::vector<std::string>& words);//检查是否为cd命令
    bool check_ls(std::vector<std::string>& words);//检查是否为ls命令
    bool check_pwd(std::vector<std::string>& words);//检查是否为pwd命令
    bool check_get(std::vector<std::string> &words); //检查是否为get命令
    std::string& string_trim(std::string &s);//去除开头与末尾的空格
    void send_illegal();//向用户发送非法指令
    std::vector<std::string> word_split(std::string&s);
    std::string get_target_path(std::string &path);//根据用户指定路径 获得绝对路径
    void ls();
};
#endif