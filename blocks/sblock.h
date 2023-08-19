#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"
#include "../board/cell.h"
#include <memory>
class Cell;

class SBlock: public Block {
protected:
    char type = 'S';
    static const int HEIGHT = 2;
    static const int WIDTH = 3;

public:
    SBlock(const std::shared_ptr<Cell> cell);
    pair<int,int> getTopLeft() const override;
    ~SBlock();
};

#endif
