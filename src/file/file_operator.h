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
class file_operator{
public:
    file_operator();
    /*create new file*/
    int create_new_file(const char*path_name,mode_t mode);
    /*Write now*/
    int write_now(int file);
    /*rename for file or dir*/
    int rename_file_dir(const char* old_path,const char* new_path);
    /*Get existing file information*/
    struct stat get_file_inf(const char*path_name);
    /*delete file*/
    int delete_file(const char* path_name);
    /*create folder*/
    int create_dir(const char* path_name,mode_t mode);
    /*read folder*/
    folder read_folder(const char* path_name);
    /*delete dir
      info:The folder must be empty before deleting it
    */
    int delete_dir(const char* path_name);
    /*get working root path 
      info: The location where the executable is executed
    */
    const char* get_work_path();
    /*
    get excuteable file location
    readlink("/proc/self/exe", arr_tmp, len)
    */
    ssize_t get_exe_path(char*buf);
};
#endif