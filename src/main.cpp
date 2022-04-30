#include <iostream>
#include "./input/arg_process.h"
#include "./tool/tool_bucket.h"
#include "./signal/signal_controll.h"
using namespace std;

extern tool_bucket boosthub_tool_bucket;

int main(int argc, char **argv)
{
    //创建应用服务
    signal_controll::signal_controll();
    arg_process ARG_PROCESS(argc, &argv);
    int stateCode = ARG_PROCESS.process();   //开始任务处理
    boosthub_tool_bucket.BOOST_LOG->close(); //关闭日志文件
    return 0;
}