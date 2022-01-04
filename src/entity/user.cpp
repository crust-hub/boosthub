#include "user.h"

/**
 * @brief Construct a new user::user object
 *
 */
user::user()
{
    this->socket_fd = -1;
    this->now_path = "/";
}

/**
 * @brief setter nowpath
 *
 * @param path 新路径
 */
void user::set_nowpath(std::string path)
{
    this->now_path = path;
}

/**
 * @brief getter now_path
 *
 * @return std::string 此时所在路径
 */
std::string user::get_now_path()
{
    return this->now_path;
}

/**
 * @brief setter socket_fd
 *
 * @param fd
 */
void user::set_socket_fd(int fd)
{
    this->socket_fd = fd;
}

/**
 * @brief getter socket_fd
 *
 * @return int
 */
int user::get_socket_fd()
{
    return this->socket_fd;
}