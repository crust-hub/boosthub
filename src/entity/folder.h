#pragma once
#ifndef __FOLDER_H__
#define __FOLDER_H__
#include <iostream>
#include <vector>
#include <string>
#include "file.h"
//文件夹实体类
class folder
{
public:
    std::string path;             // 文件夹绝对路径
    std::string name;             // 文件夹名称
    std::vector<file> get_list(); //获得此文件夹下的文件列表
    void set_list(std::vector<file> list);
    folder enter_subfolder(std::string subfolder_name); //获得此文件夹下的文件夹

private:
    std::vector<file> list; //此文件夹下的文件列表
};
#endif