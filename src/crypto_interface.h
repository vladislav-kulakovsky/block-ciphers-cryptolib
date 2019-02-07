#ifndef _CRYPTO_INTERFACE_H_
#define _CRYPTO_INTERFACE_H_
#include "types.h"
#include <string>

class CryptoInterface
{
public:
	virtual ~CryptoInterface();

	virtual std::string encrypt(std::string &plaint_text) = 0;
	virtual std::string decrypt(std::string &cipher_text) = 0;
	virtual uint32 getBlockSize() const = 0;
};
#endif // !_CRYPTO_INTERFACE_H_
