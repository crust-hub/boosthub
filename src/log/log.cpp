#include "log.h"
#define DEBUG 1

/*Log file identifier*/
void boost_log::init()
{
    /*Initialize the generated log / boost.log file. If it exists,
     open the file directly without processing*/
    /*Get the absolute path of the boothub*/
    file_operator *FILE_OPERATOR = new file_operator();
    char boosthub_path[512] = {0};
    FILE_OPERATOR->get_exe_path(boosthub_path);
    strcat(boosthub_path, "/logs"); // log folder absolute path
#if DEBUG
    printf("Log folder absolute path: %s\n", boosthub_path);
#endif
    // create log dir
    FILE_OPERATOR->create_dir(boosthub_path, 0777);
    strcat(boosthub_path, "/boost.log"); // boost.log absolute path
    FILE_OPERATOR->create_new_file(boosthub_path, 0777);
#if DEBUG
    printf("Boost.log absolute path: %s\n", boosthub_path);
#endif
    std::string time_str = boosthub_time::get();
    const char *time = time_str.c_str();
#if DEBUG
    std::cout << "[Log::warn][" << time << "] "
              << "not founded boost.log" << std::endl;
#endif
    log_fd_ = fopen(boosthub_path, "a+");
#if DEBUG
    if (NULL == log_fd_)
    {
        std::cout << "[Log::warn][" << time << "] "
                  << "create boost.log filed" << std::endl;
    }
    else
    {
        std::cout << "[Log::info][" << time << "] "
                  << "boost.log ok,we get start" << std::endl;
    }
#endif
    delete FILE_OPERATOR;
}
void boost_log::check_init()
{
    if (NULL == log_fd_)
    { // If the log file is not opened successfully, retry
        init();
    }
}
/*print message*/
void boost_log::info(const char *message)
{
    check_init();
    std::string time_str = boosthub_time::get();
    const char *time = time_str.c_str();
#if DEBUG
    std::cout << "[Log::info][" << time << "] " << message << std::endl;
#endif
    fprintf(log_fd_, "[Log::info][%s] %s\n", time, message);
}
/*print error*/
void boost_log::error(const char *message)
{
    check_init();
    std::string time_str = boosthub_time::get();
    const char *time = time_str.c_str();
#if DEBUG
    std::cout << "[Log::error][" << time << "] " << message << std::endl;
#endif
    fprintf(log_fd_, "[Log::error][%s] %s\n", time, message);
}
/*print warn info*/
void boost_log::warn(const char *message)
{
    check_init();
    std::string time_str = boosthub_time::get();
    const char *time = time_str.c_str();
#if DEBUG
    std::cout << "[Log::warn][" << time << "] " << message << std::endl;
#endif
    fprintf(log_fd_, "[Log::warn][%s] %s\n", time, message);
}
/*close log file*/
void boost_log::close()
{
    if (log_fd_ != NULL)
    {
        fclose(log_fd_);
    }
    log_fd_ = NULL;
}

boost_log::~boost_log()
{
    this->close();
}