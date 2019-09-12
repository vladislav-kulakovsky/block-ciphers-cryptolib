#include "blowfish.h"
#include "utils.h"
#include <stdexcept>
#include <string>
#include <algorithm>


uint32_t Blowfish::f(const uint32_t & left){
    return ((((sbox[0][ left >> 24] + sbox[1][(left >> 16) & 255]) & mod32) ^ sbox[2][(left >> 8) & 255]) + sbox[3][left & 255]) & mod32;
}

std::string Blowfish::run(const std::string &data) {
    if (data.size() != 8) {
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    std::uint32_t left = std::stoi(data.substr(0,4), 0, 256);
    std::uint32_t right = std::stoi(data.substr(4,4), 0, 256);
    for (std::size_t i = 0; i < 16; ++i) {
        left ^= p[i];
        right ^= f(left);
        std::swap(left, right);
    }

    right ^= p[17];
    left ^= p[16];

    return intToChar(right) + intToChar(left);
}

Blowfish::Blowfish() :
    CryptoInterface(),
    p(), sbox() {}

Blowfish::Blowfish(const std::string &key) :
    Blowfish() {
    setKey(key);
}

Blowfish::~Blowfish() {
    setKey(nullptr);
}

void Blowfish::setKey(const std::string &key_) {
    if (key_.size() < 4 || key_.size() > 112) {
        throw std::runtime_error("Error: Key size does not fit defined sizes.");
    }

    for (std::size_t i = 0; i < 18; ++i) {
        p[i] = blowfish_P[i];
    }

    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = 0; j < 512; ++j) {
            sbox[i][j] = blowfish_SBOX[i][j];
        }
    }

    std::string key = key_;

    std::uint8_t s = (72 / key.size()) + 1;
    for (std::size_t i = 0; i < s; ++i) {
        key += key;
    }

    key = key.substr(0, 72);
    for (std::size_t i = 0; i < 18; ++i) {
        p[i] ^= static_cast <std::uint32_t> (std::stoi(key.substr( i << 2, 4), 0, 256));
    }

    std::string init(8, 0);
    for(uint8_t i = 0; i < 9; ++i) {
        std::string str = run(init);
        init = str;
        p[i << 1] = std::stoi(str.substr(0, 4), 0, 256);
        p[(i << 1) + 1] = std::stoi(str.substr(4, 4), 0, 256);
    }

    for(uint8_t i = 0; i < 4; ++i){
        for(uint8_t j = 0; j < 128; ++j){
            std::string str = run(init);
            init = str;
            sbox[i][j << 1] = std::stoi(str.substr(0, 4), 0, 256);
            sbox[i][(j << 1) + 1] = std::stoi(str.substr(4, 4), 0, 256);
        }
    }
}

std::string Blowfish::encrypt(const std::string &plain_text) {
    return run(plain_text);
}

std::string Blowfish::decrypt(const std::string &cipher_text) {
    std::reverse(p, p + 18);
    std::string out = run(cipher_text);
    std::reverse(p, p + 18);
    return out;
}

std::uint32_t Blowfish::getBlockSize() const {
    return 64;
}