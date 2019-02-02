#include "ecb.h"

ECB::ECB(CryptoInterface* instance_):
    instance(instance_)
{
    this->blocksize = instance_->getBlockSize();
}

std::string ECB::encrypt(std::string &plaint_text)
{
    std::string tmp = pkcs5_padding(plaint_text, blocksize);
    std::string out;
    for (size_t i = 0; i < tmp.size(); i += blocksize)
    {
        std::string block = plaint_text.substr(i, blocksize);
        out += instance->encrypt(block);
    }

    return out;
}

std::string ECB::decrypt(std::string &cipher_text)
{
    std::string result;
    for (size_t i = 0; i < cipher_text.size(); i += blocksize)
    {
        std::string block = cipher_text.substr(i, blocksize);
        result += instance->decrypt(block);
    }
}