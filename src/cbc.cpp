#include "cbc.h"

CBC::CBC(CryptoInterface* instance_, std::string &iv):
	instance(instance_),
	IV(iv)
{
	this->blocksize = instance_->getBlockSize();
}

std::string CBC::encrypt(std::string &plain_text)
{
	std::string result;
	std::string iv = IV;
	size_t currentPosition = 0;

	if (plain_text.size() >= blocksize)
	{
		for (size_t i = 0; i + blocksize <= plain_text.size(); i += blocksize)
		{
			std::string block = plain_text.substr(i, blocksize);
			std::string xored = xorStrings(iv, block);
			iv = instance->encrypt(xored);
			result += iv;
			currentPosition = i + blocksize;
		}
		if (plain_text.size() % blocksize == 0)
		{
			std::string lastIncompletesBlock(16, 16);
			std::string lastCompletesBlock = lastIncompletesBlock;
			std::string xored = xorStrings(iv, lastCompletesBlock);
			iv = instance->encrypt(xored);
			result += iv;

			return result;
		}
	}
	
	std::string lastIncompletesBlock = plain_text.substr(currentPosition, std::string::npos);
	std::string lastCompletesBlock = pkcs5_padding(lastIncompletesBlock, blocksize);
	std::string xored = xorStrings(iv, lastCompletesBlock);
	iv = instance->encrypt(xored);
	result += iv;
	
	return result;
}

std::string CBC::decrypt(std::string &cipher_text)
{
	std::string result;
	std::string iv = IV;

	for (size_t i = 0; i < cipher_text.size(); i += blocksize)
	{
		std::string ctxt_block = cipher_text.substr(i, blocksize);
		std::string decrypted_block = instance->decrypt(ctxt_block);
		result += xorStrings(decrypted_block, iv);
		iv = cipher_text.substr(i, blocksize);
	}
	result = remove_pkcs5_padding(result);

	return result;
}