#include "jblock.h"
#include <memory>

JBlock::JBlock(const std::shared_ptr<Cell> cell) {
    int row = cell->getRow();
    int col = cell->getCol();
    // first row
    coordinates.emplace_back(std::make_shared<Cell>(row, col, 'J'));
    // second row
    row++;
    for (int j = 0; j < WIDTH; ++j) {
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j, 'J');
        coordinates.emplace_back(newCell);
    }
    bottomLeft = 1; // 3
    bottomRight = 3; // 5
}

pair<int, int> JBlock::getTopLeft() const {
    return pair(coordinates[0]->getRow(), coordinates[0]->getCol());
}

JBlock::~JBlock() {
}
