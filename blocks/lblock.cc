#include "lblock.h"

LBlock::LBlock(std::shared_ptr<Cell> cell) {
    int row = cell->getRow();
    int col = cell->getCol();
    // first row
    coordinates.emplace_back(std::make_shared<Cell>(row, col+2,'L'));
    // second row
    row++;
    for (int j = 0; j < WIDTH; ++j) {
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j, 'L');
        coordinates.emplace_back(newCell);
    }
    bottomLeft = 1;
    bottomRight = 3;
}

pair<int, int> LBlock::getTopLeft() const {
    return pair(coordinates[0]->getRow(), coordinates[0]->getCol()-2);
}

LBlock::~LBlock() {
    for (std::shared_ptr<Cell>cell: coordinates) {
        // delete cell;
    }
}

