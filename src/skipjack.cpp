#include "skipjack.h"
#include <stdexcept>

Skipjack::Skipjack() :
    CryptoInterface(),
    key("")
{}

Skipjack::Skipjack(const std::string &key) :
    Skipjack() {
    setKey(key);
}

void Skipjack::setKey(const std::string & key_) {
    if (key_.size() != 10) {
        throw std::runtime_error("Error: Key must be 80 bits in length");
    }

    key = 
}