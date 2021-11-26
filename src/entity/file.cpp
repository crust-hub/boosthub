#pragma
#include"file.h"
// 函数实现
std::ostream &operator<<(std::ostream &os, file &item) {
	os << "Fd: " << item.fd << "\tName: " << item.name << "\tType: " << item.type;
	return os;
}