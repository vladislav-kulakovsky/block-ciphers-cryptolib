#ifndef _UTILS_H_
#define _UTILS_H_
#include "types.h"
#include <string>

uint32 rotl(uint32 value, uint8 count);

uint32 charToInt(std::string block);
std::string intToChar(uint32 value);

std::string xorStrings(std::string &lhs, std::string &rhs);
std::string pkcs5_padding(std::string &incomplete_block, uint8 blocksize);
std::string remove_pkcs5_padding(std::string block);

void show_usage(std::string name);

#endif // !_UTILS_H_