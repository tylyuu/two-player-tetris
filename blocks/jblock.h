#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"
#include "../board/cell.h"
#include <memory>

class Cell;

class JBlock: public Block {
    protected:
        char type = 'J';
        static const int HEIGHT = 2;
        static const int WIDTH = 3;

    public:
        JBlock( const std::shared_ptr<Cell> cell);
        pair<int,int> getTopLeft() const override;
        ~JBlock();
};

#endif
