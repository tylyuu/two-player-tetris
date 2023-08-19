#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"
#include "../board/cell.h"
#include <memory>
using namespace std;

class Cell;

class LBlock: public Block {
    protected:
        char type = 'L';
        static const int HEIGHT = 2;
        static const int WIDTH = 3;

    public:
        LBlock(const std::shared_ptr<Cell> cell);
        pair<int,int> getTopLeft() const override;
        ~LBlock();
};

#endif
