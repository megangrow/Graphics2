#include "xorshiftrplus.h"

// used for generate a good starting state for Xorshiftrplus
class Splitmix64 {
public:
    Splitmix64(uint32_t seed)
        :s{seed} {}

    
    uint64_t next() {
        uint64_t z = (s += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
    }
    
private:
    uint64_t s;
};


Xorshiftrplus::Xorshiftrplus(uint32_t seed, int num_jumps) {
    Splitmix64 splitmix{seed};

    for (int i = 0; i < 2; ++i) {
        s[i] = splitmix.next();
    }

    for (int i = 0; i < num_jumps; ++i) {
        jump();
    }
}


uint64_t Xorshiftrplus::next() {
    uint64_t x = s[0];
    uint64_t const y = s[1];
    s[0] = y;
    x ^= x << 23; // shift & xor
    x ^= x >> 17; // shift & xor
    x ^= y; // xor
    s[1] = x + y;
    return x;
}

double Xorshiftrplus::random_double() {
    return (next() >> 11) * 0x1.0p-53;
}

void Xorshiftrplus::jump() {
    static const uint64_t JUMP[] = { 0xdf900294d8f554a5, 0x170865df4b3201fc };
    
    uint64_t s0 = 0;
    uint64_t s1 = 0;
    for(int i = 0; i < sizeof(JUMP) / sizeof(*JUMP); i++)
        for(int b = 0; b < 64; b++) {
            if (JUMP[i] & UINT64_C(1) << b) {
                s0 ^= s[0];
                s1 ^= s[1];
            }
            next();
        }
    
    s[0] = s0;
    s[1] = s1;
}


