#include "folder.h"
#include "../tool/tool_bucket.h"

extern tool_bucket boosthub_tool_bucket;

/**
 * @brief 获得此文件夹下的文件列表
 *
 * @return std::vector<file>
 */
std::vector<file>
folder::get_list()
{
    return this->list;
}

/**
 * @brief setter list
 *
 * @param list
 */
void folder::set_list(std::vector<file> list)
{
    this->list = list;
}

/**
 * @brief 获得此文件夹下的文件夹
 *
 * @param subfolder_name 文件夹名称
 * @return folder 子文件夹
 */
folder folder::enter_subfolder(std::string subfolder_name)
{
    std::string path = this->path + subfolder_name;
    folder result = boosthub_tool_bucket.FILE_OPERATOR->read_folder(path.c_str());
    return result;
}