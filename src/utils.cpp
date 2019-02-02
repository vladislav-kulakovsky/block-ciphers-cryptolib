#include "utils.h"
#include <iostream>
#include <algorithm>
#include <bitset>

uint32 rotl(uint32 value, uint8 count)
{
	return (((value) << ((int)(count))) | ((value) >> (32 - (int)(count))));
}

uint32 charToInt(std::string block)
{
	if (block.size() != 4)
	{
		std::cerr << "Wrong block size" << std::endl;
		return 0;
	}

	uint32 result = 0;
	for (int i = 0; i < block.size(); i++)
	{
		result <<= 8;
		result |= (uint32)(block[i] & 0xFF);
	}

	return result;
}

std::string intToChar(uint32 value)
{
	std::string res;

	for (int i = 0; i < sizeof(uint32); i++)
	{
		res += (char)(value & 0x000000FF);
		value >>= 8;
	}

	std::reverse(res.begin(), res.end());
	return res;
}

std::string xorStrings(std::string &lhs, std::string &rhs)
{
	std::string xored_str;

	if (lhs.size() == rhs.size())
	{
		for (size_t i = 0; i < lhs.size(); i++)
		{
			xored_str += (lhs[i]) ^ (rhs[i]);
		}
	}

	return xored_str;
}

std::string pkcs5_padding(std::string &incomplete_block, uint8 blocksize)
{
	uint8 pad = static_cast<uint8>((blocksize - incomplete_block.size()) % blocksize);

	std::string padding(pad, (pad));
	return incomplete_block + padding;
}

std::string remove_pkcs5_padding(std::string block)
{
	uint8 pad = static_cast<uint8> (block[block.size()-1]);
	std::string padding(pad, (pad));

	if ((pad < block.size()) && (padding == block.substr(block.size() - pad, pad)))
		block = block.substr(0, block.size() - pad);

	return block;
}

void show_usage(std::string name)
{
	std::cerr << "Usage: " << name << " <options> INPUT_FILE OUTPUT_FILE\n"
		<< "Options:\n"
		<< "  -m, --mode <MODE>         Set mod of program. MODE may be <encrypt>, <decrypt>\n"
		<< "  -k, --key <KEY>           Set key for encryption or decryption.\n"
		<< "                            Size must be 128, 160, 192, 224 or 256 bits.\n"
		<< "  -v, --iv <IV>             Set initialization vector. Size of IV must be 128 bits.\n"
		<< "  -i, --inp <INPUT_FILE>    You can use this option ONLY with -k AND -v\n"
		<< "                            You also can set INPUT_FILE without options\n"
		<< "                            It is described above. Then input file must contains:\n"
		<< "                            1st line: key (128, 160, 192, 224 or 256 bits)\n"
		<< "                            2nd line: 128-bit initialization vector\n"
		<< "                            3rd line: plaint text or cipher text"
		<< std::endl;
}