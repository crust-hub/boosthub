#include"log.h"
FILE* boost_log::log_fd_=NULL;//真正的内存分配
boost_log*  BOOST_LOG=new boost_log();