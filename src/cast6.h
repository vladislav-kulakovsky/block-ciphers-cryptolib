#ifndef _CAST6_H_
#define _CAST6_H_

#include "types.h"
#include "utils.h"
#include "crypto_interface.h"
#include "cast6_s_boxes.h"
#include <string>
#include <vector>

#define mod32 0xFFFFFFFFUL

class CAST256: public CryptoInterface
{
private:
	uint32 A, B, C, D; //block for plain text
	uint32 a, b, c, d, e, f, g, h; // block for key
	std::vector<std::vector<uint8>> Tr, Kr;
	std::vector<std::vector<uint32>> Tm, Km;

	uint32 f1(uint32 data, uint8 kri, uint32 kmi);
	uint32 f2(uint32 data, uint8 kri, uint32 kmi);
	uint32 f3(uint32 data, uint8 kri, uint32 kmi);
	void Q(uint32 i);
	void RQ(uint32 i);
	void W(uint32 i);

	void makeKr(uint32 i);
	void makeKm(uint32 i);

	const uint32 blocksize = 16;

public:
	CAST256();
	CAST256(std::string &key);
	~CAST256();
	
	void setKey(std::string &key);
	std::string encrypt(std::string &plaint_text);
	std::string decrypt(std::string &chipher_text);

	uint32 getBlockSize() const;
};

#endif // !_CAST6_H_
