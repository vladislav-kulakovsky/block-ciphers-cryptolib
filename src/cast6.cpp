#include "cast6.h"
#include <iostream>
#include <bitset>
#include <algorithm>

CAST256::CAST256() :
	A(0), B(0), C(0), D(0),
	a(0), b(0), c(0), d(0),
	e(0), f(0), g(0), h(0)
{
	//empty
}

CAST256::CAST256(std::string &key) :
	CAST256()
{
	setKey(key);
}

CAST256::~CAST256()
{
	std::string null_key = "00000000000000000000000000000000";
	setKey(null_key);
}

uint32 CAST256::f1(uint32 data, uint8 kri, uint32 kmi)
{
	uint32 I = rotl((kmi + data) & mod32 , kri);
	uint32 Ia = I >> 24;
	uint32 Ib = (I >> 16) & 0x000000FF;
	uint32 Ic = (I >> 8) & 0x000000FF;
	uint32 Id = I & 0x000000FF;

	return (((S1[Ia] ^ S2[Ib]) - S3[Ic]) + S4[Id]) & mod32; // operation & 0xFFFFFFFF is % 2^32
}

uint32 CAST256::f2(uint32 data, uint8 kri, uint32 kmi)
{
	uint32 I = rotl((kmi ^ data), kri);
	uint32 Ia = I >> 24;
	uint32 Ib = (I >> 16) & 0x000000FF;
	uint32 Ic = (I >> 8) & 0x000000FF;
	uint32 Id = I & 0x000000FF;

	return (((S1[Ia] - S2[Ib] + S3[Ic]) & mod32) ^ S4[Id]);
}

uint32 CAST256::f3(uint32 data, uint8 kri, uint32 kmi)
{
	uint32 I = rotl((kmi - data), kri);
	uint32 Ia = I >> 24;
	uint32 Ib = (I >> 16) & 0x000000FF;
	uint32 Ic = (I >> 8) & 0x000000FF;
	uint32 Id = I & 0x000000FF;

	return ((((S1[Ia] + S2[Ib]) & mod32) ^ S3[Ic]) - S4[Id]) & mod32;
}

void CAST256::setKey(std::string &key)
{
	size_t size = key.size();
	if ((size != 16) && (size != 20) && (size != 24) && (size != 28) && (size != 32))
	{
		std::cout << "Key length is wrong\nKey length must be 16, 20, 24, 28, 32" << std::endl;
	}

	if (size >= 16)
	{
		a = charToInt(key.substr(0, 4));
		b = charToInt(key.substr(4, 4));
		c = charToInt(key.substr(8, 4));
		d = charToInt(key.substr(12, 4));
	}
	if (size >= 20)
	{
		e = charToInt(key.substr(16, 4));
	}
	if (size >= 24)
	{
		f = charToInt(key.substr(20, 4));
	}
	if (size >= 28)
	{
		g = charToInt(key.substr(24, 4));
	}
	if (size == 32)
	{
		h = charToInt(key.substr(28, 4));
	}

	uint32 Cm = 0x5A827999;
	uint32 Mm = 0x6ED9EBA1;
	uint32 Cr = 19;
	uint32 Mr = 17;

	Km.resize(12);
	Kr.resize(12);

	for (auto& row : Km)
		row.resize(4);
	for (auto& row : Kr)
		row.resize(4);

	Tm.resize(8);
	Tr.resize(8);

	for (auto& row : Tm)
		row.resize(24);
	for (auto& row : Tr)
		row.resize(24);

	for (size_t i = 0; i < 24; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			Tm[j][i] = Cm;
			Cm = (Cm + Mm) & mod32;
			Tr[j][i] = Cr;
			Cr = (Cr + Mr) & 0x1F; //it is the same % 32
		}
	}

	for (int i = 0; i < 12; i++)
	{
		W(2 * i);
		W(2 * i + 1);
		makeKr(i);
		makeKm(i);
	}
}

void CAST256::W(uint32 i)
{
	g ^= f1(h, Tr[0][i], Tm[0][i]);
	f ^= f2(g, Tr[1][i], Tm[1][i]);
	e ^= f3(f, Tr[2][i], Tm[2][i]);
	d ^= f1(e, Tr[3][i], Tm[3][i]);
	c ^= f2(d, Tr[4][i], Tm[4][i]);
	b ^= f3(c, Tr[5][i], Tm[5][i]);
	a ^= f1(b, Tr[6][i], Tm[6][i]);
	h ^= f2(a, Tr[7][i], Tm[7][i]);
}

void CAST256::makeKr(uint32 i)
{
	Kr[i][0] = a & 0x0000001F; // 5LSB(a)
	Kr[i][1] = c & 0x0000001F;
	Kr[i][2] = e & 0x0000001F;
	Kr[i][3] = g & 0x0000001F;
}

void CAST256::makeKm(uint32 i)
{
	Km[i][0] = h;
	Km[i][1] = f;
	Km[i][2] = d;
	Km[i][3] = b;
}

void CAST256::Q(uint32 i)
{
	C ^= f1(D, Kr[i][0], Km[i][0]);
	B ^= f2(C, Kr[i][1], Km[i][1]);
	A ^= f3(B, Kr[i][2], Km[i][2]);
	D ^= f1(A, Kr[i][3], Km[i][3]);
}

void CAST256::RQ(uint32 i)
{
	D ^= f1(A, Kr[i][3], Km[i][3]);
	A ^= f3(B, Kr[i][2], Km[i][2]);
	B ^= f2(C, Kr[i][1], Km[i][1]);
	C ^= f1(D, Kr[i][0], Km[i][0]);
}

std::string CAST256::encrypt(std::string &plaint_text)
{
	if (plaint_text.size() != 16)
	{
		std::cout << "Error encrypt" << std::endl;
		exit(1);
	}

	A = charToInt(plaint_text.substr(0, 4));
	B = charToInt(plaint_text.substr(4, 4));
	C = charToInt(plaint_text.substr(8, 4));
	D = charToInt(plaint_text.substr(12, 4));

	for (int i = 0; i < 6; i++)
		Q(i);
	for (int i = 6; i < 12; i++)
		RQ(i);

	return intToChar(A) + intToChar(B) + intToChar(C) + intToChar(D);
}

std::string CAST256::decrypt(std::string &cipher_text)
{
	std::reverse(Kr.begin(), Kr.end());
	std::reverse(Km.begin(), Km.end());
	std::string result = encrypt(cipher_text);
	std::reverse(Kr.begin(), Kr.end());
	std::reverse(Km.begin(), Km.end());

	return result;
}

uint32 CAST256::getBlockSize() const
{
	return blocksize;
}
