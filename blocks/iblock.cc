#include "iblock.h"
#include <memory>

IBlock::IBlock( const std::shared_ptr<Cell> cell) {
    int row = cell->getRow();
    int col = cell->getCol();
    for (int j = 0; j < WIDTH; ++j) { // iblock is 1x4
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j, 'I');
        coordinates.emplace_back(newCell);
    }
    bottomLeft = 0; 
    bottomRight = WIDTH - 1; 
}

pair<int, int> IBlock::getTopLeft() const {
    return pair(coordinates[0]->getRow(), coordinates[0]->getCol());
}

IBlock::~IBlock() {}
