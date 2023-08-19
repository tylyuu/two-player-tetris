#ifndef FBLOCK_H
#define FBLOCK_H

#include "block.h"
#include "../board/cell.h"
#include <memory>
class Cell;

class FBlock: public Block {
    protected:
        char type = 'F';
        static const int HEIGHT = 1;
        static const int WIDTH = 1;

    public:
        FBlock();
        pair<int,int> getTopLeft() const override;
        ~FBlock();
};

#endif
