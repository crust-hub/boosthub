#include "file_operator.h"
file_operator::file_operator()
{
}
/*create new file*/
/**
 * @brief 创建新文件
 *
 * @param path_name 文件pathname
 * @param mode 权限模式
 * @return int
 */
int file_operator::create_new_file(const char *path_name, mode_t mode)
{
    int flags = O_CREAT | O_WRONLY; //|O_TRUNC
    return open(path_name, flags, mode);
}

/*Write now*/
/**
 * @brief 立即写入文件
 *
 * @param file 文件描述符
 * @return int
 */
int file_operator::write_now(int file)
{
    return fsync(file);
}

/*rename for file or dir*/
/**
 * @brief 文件重命名
 *
 * @param old_path 老的路径
 * @param new_path 新的路径
 * @return int
 */
int file_operator::rename_file_dir(const char *old_path, const char *new_path)
{
    // operator
    return rename(old_path, new_path);
}

/*Get existing file information*/
/**
 * @brief 获得文件相关信息
 *
 * @param path_name 文件pathname
 * @return struct stat
 */
struct stat file_operator::get_file_inf(const char *path_name)
{
    struct stat buf;
    stat(path_name, &buf);
    return buf;
}

/*delete file*/
/**
 * @brief 删除文件
 *
 * @param path_name
 * @return int
 */
int file_operator::delete_file(const char *path_name)
{
    return unlink(path_name);
}

/*create folder*/
/**
 * @brief 创建文件夹
 *
 * @param path_name
 * @param mode
 * @return int
 */
int file_operator::create_dir(const char *path_name, mode_t mode)
{
    // umask(0);
    return mkdir(path_name, mode);
}

/*read folder*/
/**
 * @brief 读取文件夹
 *
 * @param path_name
 * @return folder
 */
folder file_operator::read_folder(const char *path_name)
{
    std::vector<file> list;
    DIR *dp = opendir(path_name);
    struct dirent *d;
    while ((d = readdir(dp)) != NULL)
    {
        // printf("fd:%d  name:%s  type:%u  \n",(int)d->d_ino,d->d_name,d->d_type);
        file finded;
        finded.fd = d->d_ino;
        finded.name = std::string(d->d_name);
        finded.type = d->d_type == 4 ? 'd' : 'f';
        list.push_back(finded);
    }
    folder result;
    result.name = std::string(path_name);
    result.path = std::string(path_name);
    result.set_list(list);
    closedir(dp);
    return result;
}

/**
 * @brief 检查文件夹是否存在
 *
 * @param path
 * @return true
 * @return false
 */
bool file_operator::check_folder_path_real(const char *path)
{
    DIR *dp = NULL;
    dp = opendir(path);
    if (dp != NULL)
    {
        /*查看问价夹信息*/
        closedir(dp);
        return true;
    }
    return false;
}

/**
 * @brief 删除文件夹（删除的文件夹内容必须为空）
 *
 * @param path_name
 * @return int
 */
int file_operator::delete_dir(const char *path_name)
{
    return rmdir(path_name);
}

/**
 * @brief 获得用户在哪里开启的boosthub
 *
 * @return const char*
 */
const char *file_operator::get_work_path()
{
    char buf[512] = {0};
    const char *res = getcwd(buf, sizeof(buf));
    return res;
}

/**
 * @brief 获得boosthub可执行问价在哪里
 *
 * @param buf
 * @return ssize_t
 */
ssize_t file_operator::get_exe_path(char *buf)
{
    char path[512] = {0};
    ssize_t res = readlink("/proc/self/exe", path, sizeof(path));
    /*There is an executable file at the end of the path that needs to be removed*/
    for (int i = strlen(path) - 1; i >= 0; --i)
    {
        if (path[i] != '/')
        {
            path[i] = '\0';
        }
        else
        {
            break;
        }
    }
    strcpy(buf, path);
    return res;
}

/**
 * @brief 打开文件
 *
 * @param path 路径
 * @param mode 打开模式
 * @return FILE* 文件指针
 */
FILE *file_operator::open_file(std::string path, const char *mode)
{
    FILE *file = NULL;
    if (path.empty() || mode == NULL)
    {
        return file;
    }
    file = fopen(path.c_str(), mode);
    return file;
}

/**
 * @brief 文件关闭
 *
 * @param file 文件描述符
 */
void file_operator::close_file(FILE *file)
{
    if (file != NULL)
        fclose(file);
}