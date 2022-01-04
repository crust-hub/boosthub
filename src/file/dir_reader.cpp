#include "dir_reader.h"

/**
 * @brief Construct a new dir reader::dir reader object
 *
 */
dir_reader::dir_reader()
{
    this->URI_ = "";
}

/**
 * @brief Construct a new dir reader::dir reader object
 *
 * @param URI
 */
dir_reader::dir_reader(std::string URI)
{
    this->URI_ = URI;
}

/**
 * @brief getter URI
 *
 * @return std::string
 */
std::string dir_reader::get_URI()
{
    return this->URI_;
}