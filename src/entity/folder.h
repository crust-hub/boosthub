#pragma once
#ifndef __FOLDER_H__
#define __FOLDER_H__
#include<iostream>
#include<vector>
#include<string>
#include"file.h"
class folder{
public:
    std::string path;//absolute path
    std::string name;//folder name
    std::vector<file> get_list();
    void set_list(std::vector<file> list);
    folder enter_subfolder(std::string subfolder_name);
private:
    std::vector<file> list;
};
#endif