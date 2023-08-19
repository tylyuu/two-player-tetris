#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"
#include "../board/cell.h"
#include <memory>
class Cell;

class OBlock: public Block {
    protected:
        char type = 'O';
        static const int HEIGHT = 2;
        static const int WIDTH = 2;

    public:
        OBlock(std::shared_ptr<Cell> cell);
        pair<int,int> getTopLeft() const override;
        ~OBlock();
};

#endif
