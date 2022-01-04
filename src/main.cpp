#include <iostream>
#include "./tool/tool.h"
using namespace std;
int main(int argc, char **argv)
{
    arg_process ARG_PROCESS(argc, &argv);
    ARG_PROCESS.process();
    return 0;
}