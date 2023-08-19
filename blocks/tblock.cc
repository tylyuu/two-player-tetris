#include "tblock.h"

TBlock::TBlock( const std::shared_ptr<Cell> cell) {
    int row = cell->getRow();
    int col = cell->getCol();
    // first row
    for (int j = 0; j < WIDTH; ++j) {
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j, 'T');
        coordinates.emplace_back(newCell);
    }
    // second row
    row++;
    coordinates.emplace_back(std::make_shared<Cell>(row, col+1, 'T'));
    bottomLeft = 3; // 3
    bottomRight = 3; // 5
}

pair<int, int> TBlock::getTopLeft() const {
    return pair(coordinates[0]->getRow(), coordinates[0]->getCol());
}

TBlock::~TBlock() {
    for (std::shared_ptr<Cell>cell: coordinates) {
        // delete cell;
    }
}


