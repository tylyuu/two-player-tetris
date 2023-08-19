#include "fblock.h"
#include <memory>

FBlock::FBlock(){
    std::shared_ptr<Cell> newCell = std::make_shared<Cell>(3,5, '*');
    coordinates.emplace_back(newCell);
    bottomLeft = 0;
    bottomRight = 0;
}

pair<int, int> FBlock::getTopLeft() const {
    return pair<int,int>(coordinates[0]->getRow(), coordinates[0]->getCol());
}

FBlock::~FBlock() {}
