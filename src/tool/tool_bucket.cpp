#include "./tool_bucket.h"

bool tool_bucket::exist = false;

/**
 * @brief Construct a new tool bucket::tool bucket object
 *
 */
tool_bucket::tool_bucket()
{
    if (tool_bucket::exist == false)
    {
        BOOST_LOG = new boost_log();
        ARG_PROCESS = new arg_process();
        FILE_OPERATOR = new file_operator();
        tool_bucket::exist = true;
        BOOST_LOG->info("create tool_bucket instance success");
    }
    else
    {
        tool_bucket::instance.BOOST_LOG->error("tool_bucket.exist is true,it's exist");
    }
}
/**
 * @brief Destroy the tool bucket::tool bucket object
 *
 */
tool_bucket::~tool_bucket()
{
    delete BOOST_LOG;
    delete ARG_PROCESS;
    delete FILE_OPERATOR;
}

//创建一个实例
tool_bucket boosthub_tool_bucket;
tool_bucket tool_bucket::instance = boosthub_tool_bucket;