#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <random>

class Generator {
private:
    std::vector<char> bag;
    std::mt19937 rng;

public:
    Generator();
    void refill();
    char next();
};

#endif // GENERATOR_H
