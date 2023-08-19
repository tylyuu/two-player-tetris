#include "block.h"
#include "../board/board.h"
#include "../board/cell.h"
#include <memory>

vector<std::shared_ptr<Cell>> Block::getCoordinates() const {
    return coordinates;
}

std::shared_ptr<Cell> Block::getBottomLeft() const {
    return coordinates[bottomLeft];
}

std::shared_ptr<Cell> Block::getBottomRight() const {
    return coordinates[bottomRight];
}

vector<std::shared_ptr<Cell>> Block::rotate(const string& direction) {
    std::vector<std::shared_ptr<Cell>> newBlock;
    if (direction == "clockwise") {
        for (std::shared_ptr<Cell> cell : coordinates) {
            int relativeRow = cell->getRow() - getBottomRight()->getRow();
            int relativeCol = cell->getCol() - getBottomRight()->getCol();
            int newRow = getBottomLeft()->getRow() + relativeCol;
            int newCol = getBottomLeft()->getCol() - relativeRow;
            newBlock.emplace_back(std::make_shared<Cell>(newRow, newCol, cell->getChar()));
        }
    } else if (direction == "counterclockwise") {
        for (std::shared_ptr<Cell> cell : coordinates) {
            int relativeRow = cell->getRow() - getBottomLeft()->getRow();
            int relativeCol = cell->getCol() - getBottomLeft()->getCol();

            int newRow = getBottomRight()->getRow() - relativeCol;
            int newCol = getBottomRight()->getCol() + relativeRow;

            newBlock.emplace_back(std::make_shared<Cell>(newRow, newCol, cell->getChar()));
        }
    }

    return newBlock;
}

vector<std::shared_ptr<Cell>> Block::move(const string& direction) {
    std::vector<std::shared_ptr<Cell>> newBlock;
    // detect collisions for any movement
    if (direction == "left") {
        for (std::shared_ptr<Cell> cell : coordinates) {
            newBlock.emplace_back(std::make_shared<Cell>(cell->getRow(), cell->getCol()-1, cell->getChar()));
        }
    } else if (direction == "right") {
        for (std::shared_ptr<Cell> cell : coordinates) {
            newBlock.emplace_back(std::make_shared<Cell>(cell->getRow(), cell->getCol()+1, cell->getChar()));
        }
    } else if (direction == "down") {
        for (std::shared_ptr<Cell> cell : coordinates) {
            newBlock.emplace_back(std::make_shared<Cell>(cell->getRow()+1, cell->getCol(), cell->getChar()));
        }
    }

    return newBlock;
}

void Block::updateCoordinates(vector<std::shared_ptr<Cell>> cells) {
    coordinates = cells;
}
