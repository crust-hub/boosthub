#include "folder.h"
#include "../tool/tool.h"
/**
 * @brief 获得此文件夹下的文件列表
 *
 * @return std::vector<file>
 */
std::vector<file> folder::get_list()
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
    tool_bucket *TOOL = new tool_bucket();
    std::string path = this->path + subfolder_name;
    folder result = TOOL->FILE_OPERATOR->read_folder(path.c_str());
    delete TOOL;
    return result;
}