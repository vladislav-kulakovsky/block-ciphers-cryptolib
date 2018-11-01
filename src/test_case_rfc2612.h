#ifndef _TEST_CASE_RFC2612_H_
#define _TEST_CASE_RFC2612_H_

#include "types.h"
#include <vector>

std::vector<uint8> test_key128 = {
	0x23, 0x42, 0xbb, 0x9e,
	0xfa, 0x38, 0x54, 0x2c,
	0x0a, 0xf7, 0x56, 0x47,
	0xf2, 0x9f, 0x61, 0x5d
};

std::vector<uint8> test_key192 = {
	0x23, 0x42, 0xbb, 0x9e,
	0xfa, 0x38, 0x54, 0x2c,
	0xbe, 0xd0, 0xac, 0x83,
	0x94, 0x0a, 0xc2, 0x98,
	0xba, 0xc7, 0x7a, 0x77,
	0x17, 0x94, 0x28, 0x63
};

std::vector<uint8> test_key256 = {
	0x23, 0x42, 0xbb, 0x9e,
	0xfa, 0x38, 0x54, 0x2c,
	0xbe, 0xd0, 0xac, 0x83,
	0x94, 0x0a, 0xc2, 0x98,
	0x8d, 0x7c, 0x47, 0xce,
	0x26, 0x49, 0x08, 0x46,
	0x1c, 0xc1, 0xb5, 0x13,
	0x7a, 0xe6, 0xb6, 0x04
};

std::vector<uint8> plain_text = {
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};

#endif // !_TEST_CASE_RFC2612_H_