#ifndef TEXT_H
#define TEXT_H

#include "observer.h"
#include "../board/board.h"
#include "../board/game.h"
#include "../board/player.h"
#include <iostream>

class Game;

class TextObserver : public Observer
{
    std::shared_ptr<Game> game;
    void displayDivider() ;
    void printBoard(std::shared_ptr<Board> firstBoard, std::shared_ptr<Board> secondBoard);
    void printNextBlockTop(char block);
    void printNextBlockBottom(char block);
    void printNextBlock(char firstBlock, char secondBlock);
    void printLostScreen(int index);

public:
    TextObserver(std::shared_ptr<Game> game);
    ~TextObserver();
    void notify() override;
};

#endif
