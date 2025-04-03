#pragma once

#include <cstdint>

using std::uint32_t;
using std::uint64_t;

class Xorshiftrplus {
public:
    Xorshiftrplus(uint32_t seed, int num_jumps=0);

    uint64_t next();
    double random_double();
    
private:
    uint64_t s[2];

    void jump();
};


