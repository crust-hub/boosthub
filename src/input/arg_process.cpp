#include "arg_process.h"

arg_process::arg_process()
{
    _argc = 0;
    _argv = nullptr;
}

/**
 * @brief Construct a new arg process::arg process object
 *
 * @param argc 参数个数
 * @param argv 参数内容
 */
arg_process::arg_process(int argc, char ***argv)
{
    _argc = argc;
    _argv = *(argv);
}

/**
 * @brief 处理与相应任务执行
 *
 * @return int
 */
int arg_process::process()
{
    if (_argc == 0 || _argv == nullptr)
    {
        return this->ERROR;
    }
    for (int i = 0; i < _argc; i++)
    {
        printf("%s\n", _argv[i]);
    }
    return this->DOWNLOADFILE;
}