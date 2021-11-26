#include"folder.h"
#include"../tool/tool.h"
std::vector<file> folder::get_list(){
    return this->list;
}
void folder::set_list(std::vector<file> list){
    this->list=list;
}
folder folder::enter_subfolder(std::string subfolder_name){
    tool_bucket* TOOL=new tool_bucket();
    std::string path=this->path+subfolder_name;
    folder result= TOOL->FILE_OPERATOR->read_folder(path.c_str());
    delete TOOL;
    return result;
}