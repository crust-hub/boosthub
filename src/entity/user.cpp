#include"user.h"
user::user(){
    this->socket_fd=-1;
    this->now_path="/";
}
void user::set_nowpath(std::string path){
    this->now_path=path;
}
std::string user::get_now_path(){
    return this->now_path;
}
void user::set_socket_fd(int fd){
    this->socket_fd=fd;
}
int  user::get_socket_fd(){
    return this->socket_fd;
}