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
class file_operator{
public:
    /*create new file*/
    static int create_new_file(const char*path_name,mode_t mode){
        int flags=O_CREAT|O_WRONLY;//|O_TRUNC
        return open(path_name,flags,mode);
    }
    /*Write now*/
    static int write_now(int file){
        return fsync(file);
    }
    /*rename for file or dir*/
    static int rename_file_dir(const char* old_path,const char* new_path){
        return rename(old_path,new_path);
    }
    /*Get existing file information*/
    static struct stat get_file_inf(const char*path_name){
        struct stat buf;
        stat(path_name, &buf);
        return buf;
    }
    /*delete file*/
    static int delete_file(const char* path_name){
        return unlink(path_name);
    }
    /*create folder*/
    static int create_dir(const char* path_name,mode_t mode){
        //umask(0);
        return mkdir(path_name,mode);
    }
    /*read folder*/
    static void read_folder(const char* path_name){
        DIR* dp=opendir(path_name);
        struct dirent *d;
        while((d=readdir(dp))!=NULL){
            printf("fd:%d  name:%s  type:%u  \n",(int)d->d_ino,d->d_name,d->d_type);
        }
        closedir(dp);
    }
    /*delete dir
      info:The folder must be empty before deleting it
    */
    static int delete_dir(const char* path_name){
        return rmdir(path_name);
    }
    /*get working root path 
      info: The location where the executable is executed
    */
    static const char* get_work_path(){
        char buf[512]={0};
        const char *res=getcwd(buf, sizeof(buf));
        return res;
    }
    /*
    get excuteable file location
    readlink("/proc/self/exe", arr_tmp, len)
    */
    static ssize_t get_exe_path(char*buf){
        char path[512]={0};
        ssize_t res=readlink("/proc/self/exe",path,sizeof(path));
        /*There is an executable file at the end of the path that needs to be removed*/
        for(int i=strlen(path)-1;i>=0;--i){
            if(path[i]!='/'){
                path[i]='\0';
            }else{
                break;
            }
        }
        strcpy(buf,path);
        return res;
    }
};
#endif