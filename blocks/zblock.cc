#include "zblock.h"

ZBlock::ZBlock( const std::shared_ptr<Cell> cell) {
    int row = cell->getRow();
    int col = cell->getCol();
    // first row
    for (int j = 1; j < WIDTH; ++j) {
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j-1, 'Z');
        coordinates.emplace_back(newCell);
    }
    // second row
    row++;
    for (int j = 1; j < WIDTH; ++j) {
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j, 'Z');
        coordinates.emplace_back(newCell);
    }
    bottomLeft = 2;
    bottomRight = 3;
}

pair<int, int> ZBlock::getTopLeft() const {
    return pair(coordinates[0]->getRow(), coordinates[0]->getCol());
}

ZBlock::~ZBlock() {}
