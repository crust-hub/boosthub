#include <iostream>
#include "./input/arg_process.h"
using namespace std;
int main(int argc, char **argv)
{
    //创建应用服务
    arg_process ARG_PROCESS(argc, &argv);
    ARG_PROCESS.process(); //开始任务处理
    return 0;
}