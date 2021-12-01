#include"file_operator.h"
file_operator::file_operator(){
    
}
/*create new file*/
int file_operator::create_new_file(const char*path_name,mode_t mode){
    int flags=O_CREAT|O_WRONLY;//|O_TRUNC
    return open(path_name,flags,mode);
}
/*Write now*/
int file_operator::write_now(int file){
    return fsync(file);
}
/*rename for file or dir*/
int file_operator::rename_file_dir(const char* old_path,const char* new_path){
    //operator
    return rename(old_path,new_path);
}
/*Get existing file information*/
struct stat file_operator::get_file_inf(const char*path_name){
    struct stat buf;
    stat(path_name, &buf);
    return buf;
}
/*delete file*/
int file_operator::delete_file(const char* path_name){
    return unlink(path_name);
}
/*create folder*/
int file_operator::create_dir(const char* path_name,mode_t mode){
    //umask(0);
    return mkdir(path_name,mode);
}
/*read folder*/
folder file_operator::read_folder(const char* path_name){
    std::vector<file> list;
    DIR* dp=opendir(path_name);
    struct dirent *d;
    while((d=readdir(dp))!=NULL){
      //printf("fd:%d  name:%s  type:%u  \n",(int)d->d_ino,d->d_name,d->d_type);
      file finded;
      finded.fd=d->d_ino;
      finded.name=std::string(d->d_name);
      finded.type=d->d_type==4?'d':'f';
      list.push_back(finded);
    }
    folder result;
    result.name=std::string(path_name);
    result.path=std::string(path_name);
    result.set_list(list);
    closedir(dp);
    return result;
}

/*检查文件夹是否存在*/
bool file_operator::check_folder_path_real(const char* path){
    DIR* dp=NULL;
    dp=opendir(path);
    if(dp!=NULL){
        /*查看问价夹信息*/
        closedir(dp);
        return true;
    }
    return false;
}


/*delete dir
  info:The folder must be empty before deleting it
*/
int file_operator::delete_dir(const char* path_name){
    return rmdir(path_name);
}
/*get working root path 
  info: The location where the executable is executed
*/
const char* file_operator::get_work_path(){
    char buf[512]={0};
    const char *res=getcwd(buf, sizeof(buf));
    return res;
}
/*
get excuteable file location
readlink("/proc/self/exe", arr_tmp, len)
*/
ssize_t file_operator::get_exe_path(char*buf){
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
