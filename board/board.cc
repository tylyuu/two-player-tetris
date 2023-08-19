#include "cell.h"
#include "board.h"
#include <memory>

const int NUM_ROWS = 18;
const int NUM_COLS = 11;

Board::Board() {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            std::shared_ptr<Cell>newCell = std::make_shared<Cell>(i,j);
            cells.emplace_back(newCell);
        }
    }
}

Board::~Board() {}

void Board::resetBlind() {
    blind = !blind;
}

char Board::getState(int row, int col) const {
    if (blind) {
        if ( row >= 3 && row <= 9) {
            return '?';
        }
    } else if (currentBlock != nullptr) {
        std::vector<std::shared_ptr<Cell>> current = currentBlock->getCoordinates();
        for (auto c:current) {
            if (row == c->getRow() && col == c->getCol()) {
                return c->getChar();
            }
        }
    }
    int pos = row * NUM_COLS + col;
    return cells.at(pos)->getChar();
}

std::shared_ptr<Block> Board::BlockFactory::build(char block, int row, int col){
    switch (block) {
        case 'I':
            return std::make_shared<IBlock>( std::make_shared<Cell>(row, col));
        case 'J':
            return std::make_shared<JBlock>(std::make_shared<Cell>(row, col));
        case 'L':
            return std::make_shared<LBlock>(std::make_shared<Cell>(row, col));
        case 'O':
            return std::make_shared<OBlock>(std::make_shared<Cell>(row, col));
        case 'S':
            return std::make_shared<SBlock>(std::make_shared<Cell>(row, col));
        case 'Z':
            return std::make_shared<ZBlock>(std::make_shared<Cell>(row, col));
        case 'T':
            return std::make_shared<TBlock>(std::make_shared<Cell>(row, col));
        case 'F':
            return std::make_shared<FBlock>();
    }
}




bool Board::canSet(std::shared_ptr<Block>block) const {
    for (auto c: block->getCoordinates()) {
        int pos = c->getRow() * NUM_COLS + c->getCol();
        if (cells.at(pos)->getChar()!=' ' || pos < NUM_COLS*3) {
            return false;
        }
    }
    return true;
}

bool Board::initBlock(char block, int row , int col ) {
    std::shared_ptr<BlockFactory> factory;
    std::shared_ptr<Block>temp = factory->build(block, row, col);
    if (canSet(temp)) {
        currentBlock = temp;
        return true;
    } else {
        return false;
    }
}


bool Board::setCurrentBlock(char block) {
    int row = currentBlock->getTopLeft().first;
    int col = currentBlock->getTopLeft().second;
    std::shared_ptr<BlockFactory> factory;
    std::shared_ptr<Block>temp = factory->build(block, row, col);
    if (!canSet(temp)) {
        return false;
    } else {
        initBlock(block, row, col);
        return true;
    }
}

bool Board::canAction(vector<std::shared_ptr<Cell>> coordinates) const { 
    for (auto c: coordinates){
        int row = c->getRow();
        int col = c->getCol();
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) return false;
        else {
            int pos = row * NUM_COLS + col; // index on board
            if (cells.at(pos)->getChar() != ' ') return false;
        }
    }
    return true;
}

void Board::actionBlock(const std::string &direction, const std::string &action) {
    vector<std::shared_ptr<Cell>> temp;
    if (action == "move") {
        temp = currentBlock->move(direction);
    } else if (action == "rotate") {
        temp = currentBlock->rotate(direction);
    }
    if (canAction(temp)){
        currentBlock->updateCoordinates(temp);
    } else if (action == "move") {
        doneMove = true;
    } else if (action == "rotate") {
        doneRotate = true;
    }
}

bool Board::dropBlock() {
    specialCount++;
    bool canDrop = true;
    while (!doneMove){
        actionBlock("down", "move");
    }
    for (auto c: currentBlock->getCoordinates()){
        int row = c->getRow();
        int col = c->getCol();
        int pos = row * NUM_COLS + col;
        if (pos < NUM_COLS*3) canDrop = false;
        cells[pos]->set(c->getChar());
    }
    currentBlock = nullptr;
    return canDrop;
}

bool Board::canSpecial() const {
    return specialCount == 4;
}

void Board::resetSpecial() {
    specialCount = 0;
}

void Board::resetAction(const string &action) {
    if (action == "move") {
        doneMove = false;
    } else if (action == "rotate") {
        doneRotate = false;
    }
}

bool Board::actionDone(const string &action) const {
    if (action == "move") {
        return doneMove;
    } else if (action == "rotate") {
        return doneRotate;
    }
    return false; // invalid param
}

int Board::clearRow() {
    int count = 0;
    bool isFilled = false;
    for (int i = 3; i < NUM_ROWS; i++){
        for (int j = 0; j < NUM_COLS; j++) {
            int pos = i * NUM_COLS + j;
            if (cells.at(pos)->getChar()==' ') break;
            if (j == NUM_COLS-1) isFilled = true;
        }
        // clear row
        if (isFilled){
            count++;
            for (int t = i-1; t >= 3; t--) {
                for (int s = 0; s < NUM_COLS; s++) {
                    int pos = t * NUM_COLS + s;
                    int newPos = (t+1) * NUM_COLS + s;
                    cells.at(newPos) = std::make_shared<Cell>(t+1,s, cells.at(pos)->getChar());
                }
            }
            for (int s = 0; s < NUM_COLS; s++) {
                int pos = 3 * NUM_COLS + s;
                cells.at(pos) = std::make_shared<Cell>(3,s);
            }
            isFilled = false;
        }
    }
    return count;
}
