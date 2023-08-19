#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "observer.h"
#include "window.h"
#include "../board/board.h"
#include "../board/game.h"
#include "../board/player.h"
#include <map>
#include <memory>

class Game;
class SfmlWindow;

class GraphicsObserver : public Observer
{
    std::shared_ptr<Game> game;
    SfmlWindow window;
    static const  int SCREEN_WIDTH = 950;
    static const int SCREEN_HEIGHT = 660;
    static const int BLOCK_SIZE = 25; // size of each cell
    static const int CELL_BORDER = 3;
    static const int GRID_ADJUSTMENT = 2;
    static int textColour;
    static int backgroundColour;

    int boardWidth;
    int boardHeight;
    int scoreDimension;
    int nextHeight;
    int padding;
    void printBoard(std::shared_ptr<Board> firstBoard, std::shared_ptr<Board> secondBoard);
    void printNextBlock(char firstBlock, char secondBlock);
    void printLostScreen(int index);
    void printScore(int boardNumber);
    void drawCellType(int x, int y, int colour, char block);

    void setWindowInactive(){
        window.setInActive();
    }

public:
    GraphicsObserver(std::shared_ptr<Game> game);
    ~GraphicsObserver() override;
    void toggleSfx() ;
    void run();
    void notify() override;
};

#endif