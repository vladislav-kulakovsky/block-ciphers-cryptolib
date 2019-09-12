#ifndef __BLOWFISH_H__
#define __BLOWFISH_H__

#include "crypto_interface.h"
#include "blowfish_const.h"

#define mod32 0xFFFFFFFFUL

class Blowfish : public CryptoInterface {
private:
    std::uint32_t p[18], sbox[4][512];
    std::uint32_t f(const std::uint32_t &left);
    std::string run(const std::string &data);

public:
    Blowfish();
    Blowfish(const std::string &key);
    void setKey(const std::string & key);
    std::string encrypt(const std::string &plain_text);
    std::string decrypt(const std::string &cipher_text);
    std::uint32_t getBlockSize() const;
};

#endif //__BLOWFISH_H__