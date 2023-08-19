#include "oblock.h"

OBlock::OBlock(const std::shared_ptr<Cell> cell){
    int row = cell->getRow();
    int col = cell->getCol();

    // first row
    for (int j = 0; j < WIDTH; ++j) {
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j, 'O');
        coordinates.emplace_back(newCell);
    }

    // second row
    row++;
    for (int j = 0; j < WIDTH; ++j) {
        std::shared_ptr<Cell> newCell = std::make_shared<Cell>(row, col+j, 'O');
        coordinates.emplace_back(newCell);
    }
    bottomLeft = WIDTH; 
    bottomRight = HEIGHT * WIDTH - 1;
}

pair<int, int> OBlock::getTopLeft() const {
    return pair(coordinates[0]->getRow(), coordinates[0]->getCol());
}

OBlock::~OBlock() {
    for (std::shared_ptr<Cell>cell: coordinates) {
    }
}


