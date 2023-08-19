#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"
#include "../board/cell.h"
#include <memory>
class Cell;

class ZBlock: public Block {
protected:
    char type = 'Z';
    static const int HEIGHT = 2;
    static const int WIDTH = 3;

public:
    ZBlock( const std::shared_ptr<Cell> cell);
    pair<int,int> getTopLeft() const override;
    ~ZBlock();
};

#endif
