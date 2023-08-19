#include "generator.h"

Generator::Generator() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng = std::mt19937(seed);
    refill();
}

void Generator::refill() {
        bag = {'I', 'J', 'L', 'O', 'T', 'Z'};
        std::shuffle(bag.begin(), bag.end(), rng);
}

char Generator::next() {
    if(bag.empty()) refill();
    char nextPiece = bag.back();
    bag.pop_back();
    return nextPiece;
}
