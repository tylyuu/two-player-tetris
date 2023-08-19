#ifndef TBLOCK_H
#define TBLOCK_H

#include "block.h"
#include "../board/cell.h"
#include <memory>
class Cell;

class TBlock: public Block {
protected:
    char type = 'T';
    static const int HEIGHT = 2;
    static const int WIDTH = 3;

public:
    TBlock( const std::shared_ptr<Cell> cell);
    pair<int,int> getTopLeft() const override;
    ~TBlock();
};

#endif
