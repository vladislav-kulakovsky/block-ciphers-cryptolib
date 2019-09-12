#ifndef SKIPJACK_H_
#define SKIPJACK_H_

#include "skipjack_const.h"
#include "crypto_interface.h"

class Skipjack : public CryptoInterface {
private:
    std::string key;
    std::uint16_t g_e(const std::uint16_t quarter, const std::uint32_t fourkey);
    std::uint16_t g_d(const std::uint16_t quarter, const std::uint32_t fourkey);
    void a(std::uint16_t &w1, std::uint16_t &w2, std::uint16_t &w3, std::uint16_t &w4, const std::uint16_t i);
    void b(std::uint16_t &w1, std::uint16_t &w2, std::uint16_t &w3, std::uint16_t &w4, const std::uint16_t i);
    void invA(std::uint16_t &w1, std::uint16_t &w2, std::uint16_t &w3, std::uint16_t &w4, const std::uint16_t i);
    void invB(std::uint16_t &w1, std::uint16_t &w2, std::uint16_t &w3, std::uint16_t &w4, const std::uint16_t i);

public:
    Skipjack();
    Skipjack(const std::string &key);
    void setKey(const std::string &key);
    std::string encrypt(const std::string &plain_text);
    std::string decrypt(const std::string &cipher_text);
    std::uint32_t getBlockSize() const;
};

#endif //SKIPJACK_H__