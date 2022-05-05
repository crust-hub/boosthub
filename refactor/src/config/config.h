#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <string>
#include <iostream>
class Config
{
private:
    /**
     * @brief server ip地址
     *
     */
    std::string ip;
    /**
     * @brief server 端口号
     *
     */
    int port;
    /**
     * @brief 是否打开日志
     *
     */
    bool log;

public:
    Config();

    ~Config();

    /**
     * @brief 命令行解析
     *
     * @param argc
     * @param argv
     */
    void parse(int argc, char **argv);

    /**
     * @brief 重载cout
     *
     * @param out
     * @param self
     * @return std::ostream&
     */
    friend std::ostream &operator<<(std::ostream &out, Config &self);

public:
    /**
     * @brief Get the port object
     *
     * @return int
     */
    int get_port();
    /**
     * @brief Get the ip object
     *
     * @return std::string
     */
    std::string get_ip();
    /**
     * @brief Get the log object
     *
     * @return true
     * @return false
     */
    bool get_log();
};
#endif