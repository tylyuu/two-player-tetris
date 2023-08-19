#ifndef IBLOCK_H
#define IBLOCK_H

#include <memory>

#include "block.h"
#include "../board/cell.h"

class Cell;

class IBlock: public Block {
    protected:
        char type = 'I';
        static const int HEIGHT = 1;
        static const int WIDTH = 4;

    public:
        IBlock(const std::shared_ptr<Cell> cell);
        pair<int,int> getTopLeft() const override;
        ~IBlock();
};

#endif
