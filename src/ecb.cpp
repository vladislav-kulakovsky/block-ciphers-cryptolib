#include "ecb.h"
#include <iostream>

ECB::ECB(CryptoInterface* instance_):
    instance(instance_)
{
    this->blocksize = instance_->getBlockSize();
}

std::string ECB::encrypt(std::string &plaint_text)
{
    std::string result;
    size_t current_position = 0;

    if (plaint_text.size() >= blocksize)
    {
        for (size_t i = 0; i + blocksize < plaint_text.size(); i += blocksize)
        {
            std::string block = plaint_text.substr(i, blocksize);
            result += instance->encrypt(block);
            current_position = i + blocksize;
        }
        if (plaint_text.size() % blocksize == 0)
        {
            std::string lastIncompletesBlock(blocksize,blocksize);
            result += instance->encrypt(lastIncompletesBlock);

            return result;
        }
    }

    std::string lastIncompletesBlock = plaint_text.substr(current_position, std::string::npos);
    std::string lastCompletesBlock = pkcs5_padding(lastIncompletesBlock, blocksize);
    result += instance->encrypt(lastCompletesBlock);

    return result;
}

std::string ECB::decrypt(std::string &cipher_text)
{
    std::string result;

    for (size_t i = 0; i < cipher_text.size(); i += blocksize)
    {
        std::string block = cipher_text.substr(i, blocksize);
        result += instance->decrypt(block);
    }
    result = remove_pkcs5_padding(result);
    return result;
}
