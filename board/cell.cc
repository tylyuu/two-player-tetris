#include "cell.h"

Cell::Cell(int row, int col, char c) : row{ row }, column{ col }, c{c} {}

bool Cell::isEmpty() const {
    return c == ' ';
}

char Cell::getChar() const {
    return c;
}

void Cell::set(char newChar) {
    c = newChar;
}

void Cell::unset() {
    c = ' ';
}

int Cell::getRow() const {
    return row;
}

int Cell::getCol() const {
    return column;
}

void Cell::setRow(int newRow) {
    row = newRow;
}

void Cell::setCol(int newCol) {
    column = newCol;
}
