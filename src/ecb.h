#ifndef _ECB_H_
#define _ECB_H_

#include "crypto_interface.h"
#include "types.h"
#include "utils.h"

class ECB
{
private:
    CryptoInterface* instance;
	uint32 blocksize;
public:
    ECB(CryptoInterface* instance_);
	std::string encrypt(std::string &plaint_text);
	std::string decrypt(std::string &cipher_text);
};

#endif // !_ECB_H_
