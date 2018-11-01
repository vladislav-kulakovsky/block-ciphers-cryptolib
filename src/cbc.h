#ifndef _CBC_H_
#define _CBC_H_
#include "crypto_interface.h"
#include "types.h"
#include "utils.h"

class CBC
{
private:
	std::string IV;
	CryptoInterface* instance;
	uint8 blocksize;

public:
	CBC(CryptoInterface* instance_, std::string &IV_);
	std::string encrypt(std::string &plaint_text);
	std::string decrypt(std::string &cipher_text);
};

#endif // !_CBC_H_