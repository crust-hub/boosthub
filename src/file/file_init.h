#pragma once
#ifndef __FILE_INIT__
#define __FILE_INIT__

/**
 * @brief 文件初始化器
 * 负责检查文件是否存在、主要做出不存在时的行动
 */
class file_init
{
private:
public:
    bool init();
};
#endif