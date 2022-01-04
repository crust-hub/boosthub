#include "file.h"
/**
 * @brief file overide tostring
 *
 * @param os
 * @param item
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, file &item)
{
	os << "Fd: " << item.fd << "\tName: " << item.name << "\tType: " << item.type;
	return os;
}