#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <map>
using namespace std;

#include "game.h"
#include "cell.h"
#include "subject.h"
#include "../blocks/block.h"
#include "../blocks/iblock.h"
#include "../blocks/jblock.h"
#include "../blocks/lblock.h"
#include "../blocks/oblock.h"
#include "../blocks/sblock.h"
#include "../blocks/zblock.h"
#include "../blocks/tblock.h"
#include "../blocks/fblock.h"

class Cell;

extern const int NUM_ROWS;
extern const int NUM_COLS;
extern const int BOARD_SIZE;
class Board {
    vector<std::shared_ptr<Cell>> cells;
    std::shared_ptr<Block>currentBlock;
    bool blind = false;
    bool doneMove = false;
    bool doneRotate = false;
    int specialCount = 0;
    class BlockFactory{
    public:
        std::shared_ptr<Block> build(char block, int row, int col);
    };

    public:
        Board();
        ~Board();
        char getState(int row, int col) const;
        bool initBlock(char block, int row = 3, int col = 0);
        bool setCurrentBlock(char block);
        void actionBlock(const string &direction, const string &action);
        bool dropBlock();
        bool canSet(const std::shared_ptr<Block>block) const;
        bool canAction(const vector<std::shared_ptr<Cell>> coordinates) const;
        int clearRow();
        void resetAction(const string &action);
        void resetBlind();
        bool canSpecial() const;
        void resetSpecial();
        bool actionDone(const string &action) const;
};


#endif
