#include "rng.h"

using std::random_device;

RNG::RNG() :
        RNG{random_device{}()} {
}

RNG::RNG(unsigned int seed) :
        gen_{seed},
        dis_{} {
}

unsigned long long RNG::rand() {
    return dis_(gen_);
}
