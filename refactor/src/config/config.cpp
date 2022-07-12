#include "config.h"
#include <unistd.h>
Config::Config()
{
    ip = "0.0.0.0";
    port = 8080;
    log = false;
}

Config::~Config()
{
}

void Config::parse(int argc, char **argv)
{
    std::string str = "l:p:i:";
    char ch;
    //解析命令行
    while (-1 != (ch = getopt(argc, argv, str.c_str())))
    {
        switch (ch)
        {
        case 'l':
            this->log = true; //开启日志
            break;
        case 'p':
            this->port = atoi(optarg);
            break;
        case 'i':
            this->ip = optarg;
            break;

        default:
            break;
        }
    }
}

std::ostream &operator<<(std::ostream &out, Config &self)
{
    std::cout << "Config:" << std::endl;
    std::cout << "\tip " << self.ip << std::endl;
    std::cout << "\tport " << self.port << std::endl;
    std::cout << "\tlog " << (self.log ? "true" : "false") << std::endl;
    return out;
}

int Config::get_port()
{
    return this->port;
}

std::string Config::get_ip()
{
    return this->ip;
}

bool Config::get_log()
{
    return this->log;
}