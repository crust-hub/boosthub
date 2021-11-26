#ifndef __BOOST_SHELL__
#define __BOOST_SHELL__
#include<string>
#include"../file/file_operator.h"
#include"../entity/file.h"
#include"../entity/user.h"
class tool_bucket;
class boost_shell{
private:
    std::string shell;
    file_operator FILE_TOOL;
    user USER;//用户角色
public:
    boost_shell();
    boost_shell(int socket_fd);
    void run(std::string shell);
    void set_socket_fd(int socket_fd);
    void patch(std::string&shell);
    void ls();
};
#endif