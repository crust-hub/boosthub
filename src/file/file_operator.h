#pragma once
#ifndef __FILE_OPERATOR_H__
#define __FILE_OPERATOR_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <string>
#include "../entity/folder.h"

/**
 * @brief 文件操作工具
 *
 */
class file_operator
{
public:
  file_operator();
  //创建新文件
  int create_new_file(const char *path_name, mode_t mode);
  //立即写文件
  int write_now(int file);
  //文件重命名
  int rename_file_dir(const char *old_path, const char *new_path);
  //获得文件详情
  struct stat get_file_inf(const char *path_name);
  //文件删除
  int delete_file(const char *path_name);
  //新建文件夹
  int create_dir(const char *path_name, mode_t mode);
  //读取文件夹
  folder read_folder(const char *path_name);
  /*检查文件夹是否存在*/
  bool check_folder_path_real(const char *path);
  //删除文件夹
  int delete_dir(const char *path_name);
  //开启boosthub时所在位置
  const char *get_work_path();
  //获得可执行问价所在路径
  ssize_t get_exe_path(char *buf);
  //尝试打开文件
  FILE *open_file(std::string path, const char *mode);
  //关闭文件
  void close_file(FILE *file);
};
#endif