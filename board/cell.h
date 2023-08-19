#ifndef CELL_H
#define CELL_H

#include "../display/observer.h"

class Cell {
    char c;
    int row;
    int column;

public:
    Cell(int row, int col, char c=' ');
    bool isEmpty() const;
    char getChar() const;
    void set(char newChar);
    void unset();
    int getRow() const;
    int getCol() const;
    void setRow(int newRow);
    void setCol(int newCol);
    ~Cell() = default;
};

#endif
