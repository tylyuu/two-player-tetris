#include "window.h"
#include "graphic.h"
#include <iostream>

class GraphicsObserver;

std::map<char, int> blockToColour{
        {'I', SfmlWindow::Orange},
        {'J', SfmlWindow::Red},
        {'O', SfmlWindow::Blue},
        {'L', SfmlWindow::Green},
        {'S', SfmlWindow::Cyan},
        {'T', SfmlWindow::Magenta},
        {'Z', SfmlWindow::Yellow},
        {'*', SfmlWindow::Brown}
};

std::map<char, int> blockToWidth{
        {'I', 4},
        {'J', 3},
        {'O', 2},
        {'L', 3},
        {'S', 3},
        {'T', 3},
        {'Z', 3}
};

std::map<char, int> blockToHeight{
        {'I', 1},
        {'J', 2},
        {'O', 2},
        {'L', 2},
        {'S', 2},
        {'T', 2},
        {'Z', 2}
};

int GraphicsObserver::textColour = SfmlWindow::White;
int GraphicsObserver::backgroundColour = SfmlWindow::Black;

GraphicsObserver::GraphicsObserver(std::shared_ptr<Game> game) : game{game}, window{SCREEN_WIDTH, SCREEN_HEIGHT}
{
    game->attach(this);

    boardWidth = NUM_COLS * BLOCK_SIZE;
    boardHeight = NUM_ROWS * BLOCK_SIZE;
    scoreDimension = boardWidth / 2;
    nextHeight = 5 * BLOCK_SIZE;
    padding = BLOCK_SIZE;
    printBoard(game->getBoard(1), game->getBoard(2));
    printScore(1);
    printScore(2);
    printNextBlock(game->getPlayer(1)->getNextBlock(), game->getPlayer(2)->getNextBlock());
}

GraphicsObserver::~GraphicsObserver() {
    game->detach(this);
}

void GraphicsObserver::drawCellType(int x, int y, int colour, char block)  {
        window.fillRectangle(x + GRID_ADJUSTMENT- CELL_BORDER/2, y + GRID_ADJUSTMENT- CELL_BORDER/2, BLOCK_SIZE - CELL_BORDER,
                             BLOCK_SIZE - CELL_BORDER, colour);

}

void GraphicsObserver::printBoard(std::shared_ptr<Board> firstBoard, std::shared_ptr<Board> secondBoard)  {
    // set background colour
    window.fillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundColour);

    // draw title
    window.drawVeryBigString(padding+scoreDimension*2.75, (BLOCK_SIZE/4) + BLOCK_SIZE, "TETRIS", SfmlWindow::Orange);

    // draw borders of the board
    int adjustX = padding;
    for (int board = 0; board < 2; board++) {
        if (board == 1) {
            adjustX = 3*padding + boardWidth + scoreDimension;
        }
        window.fillRectangle(adjustX-CELL_BORDER, padding + 3*BLOCK_SIZE-CELL_BORDER, boardWidth + 2*CELL_BORDER, boardHeight + 2*CELL_BORDER, textColour);
        window.fillRectangle(adjustX, padding + 3*BLOCK_SIZE, boardWidth, boardHeight, backgroundColour);
    }

    for (int board = 0; board < 2; board++) {
        for (int i = 0; i < NUM_ROWS; i++){ // board 1
            for (int j = 0; j < NUM_COLS; j++){
                int x = j * BLOCK_SIZE + padding;
                int y = i * BLOCK_SIZE + 4* BLOCK_SIZE;

                char cell;
                if (board == 0) {
                    cell = firstBoard->getState(i,j);
                } else {
                    cell = secondBoard->getState(i,j);
                    x = j * BLOCK_SIZE + boardWidth + 3*padding + scoreDimension;
                    if ( j == NUM_COLS - 1) {
                    }
                }

                if (cell == '?')
                {
                    drawCellType(x, y, textColour, cell); // blind cell
                }
                else if (cell != ' ')
                {
                    drawCellType(x, y, blockToColour[cell], cell);
                }
                else if (i == 0 || j == 0) {
                    drawCellType(x, y, backgroundColour, '1'); // top left corner
                }
                else if (i == NUM_ROWS-1 || j == NUM_COLS-1) {
                    drawCellType(x, y, backgroundColour, '4'); // dont draw over the white border
                }
                else
                {
                    drawCellType(x, y, backgroundColour, cell);
                }
            }
        }
    }
}

void GraphicsObserver::printNextBlock(char firstBlock, char secondBlock)  {
    window.fillRectangle(2*padding + boardWidth + CELL_BORDER, 3*BLOCK_SIZE + padding + boardHeight - nextHeight + CELL_BORDER, scoreDimension - 2*CELL_BORDER, nextHeight - 2*CELL_BORDER, backgroundColour);
    window.fillRectangle(SCREEN_WIDTH - scoreDimension - padding + CELL_BORDER, 3*BLOCK_SIZE + padding + boardHeight - nextHeight + CELL_BORDER, scoreDimension - 2*CELL_BORDER, nextHeight - 2*CELL_BORDER, backgroundColour);

    window.drawBigString(3.5*padding + boardWidth, 2*padding + 11*BLOCK_SIZE + 3*BLOCK_SIZE, "NEXT",
                         textColour);
    window.drawBigString(SCREEN_WIDTH - scoreDimension + padding/2, 2*padding + 11*BLOCK_SIZE + 3*BLOCK_SIZE, "NEXT",
                         textColour);

    // block
    char currBlock;
    int blockX;
    for (int whichBlock = 0; whichBlock < 2; ++whichBlock) {
        if (whichBlock == 0) currBlock = firstBlock;
        else currBlock = secondBlock;

        for (int j = 0; j < blockToHeight[currBlock]; ++j) {
            for (int i = 0; i < blockToWidth[currBlock]; ++i) {
                if (whichBlock == 0) blockX = 3*padding + i*BLOCK_SIZE + boardWidth;
                else blockX = SCREEN_WIDTH - scoreDimension + i*BLOCK_SIZE;

                if (currBlock == 'J' && i > 0 && j == 0) continue;
                if (currBlock == 'L' && i < blockToHeight[currBlock] && j == 0) continue;
                if (currBlock == 'S' && ((i == 0 && j == 0) || (i == blockToHeight[currBlock] && j == 1))) continue;
                if (currBlock == 'Z' && ((i == 0 && j == 1) || (i == blockToHeight[currBlock] && j == 0))) continue;
                if (currBlock == 'T' && ((i == 0 && j == 1) || (i == blockToHeight[currBlock] && j == 1))) continue;

                drawCellType(blockX, SCREEN_HEIGHT - 2*nextHeight + 2.25*BLOCK_SIZE + j*BLOCK_SIZE, blockToColour[currBlock], currBlock); // else or I or O
            }
        }
    }
}

void GraphicsObserver::printLostScreen(int index)  {
    window.fillRectangle(scoreDimension*1.8, SCREEN_HEIGHT/2, SCREEN_WIDTH/3, 3*BLOCK_SIZE - 2*CELL_BORDER, SfmlWindow::Orange);
    window.fillRectangle(scoreDimension*1.8, SCREEN_HEIGHT/2+scoreDimension*0.5, SCREEN_WIDTH/3, 3*BLOCK_SIZE - 2*CELL_BORDER, SfmlWindow::White);
    window.drawVeryBigString(padding+scoreDimension*1.8, SCREEN_HEIGHT/2, "PLAYER " + std::to_string(index) + " LOST :(", SfmlWindow::Black);
    window.drawBigString(padding+scoreDimension*1.8, SCREEN_HEIGHT/2+scoreDimension*0.5, "Enter Y to Restart",SfmlWindow::Orange);
    window.drawBigString(padding+scoreDimension*1.8, SCREEN_HEIGHT/2+scoreDimension*0.7, "Enter N to End Game",SfmlWindow::Orange);
}

void GraphicsObserver::printScore(int boardNumber)  {
    int adjustmentX = padding*2 + boardWidth;
    if (boardNumber == 2) adjustmentX = SCREEN_WIDTH - padding - scoreDimension;

    window.fillRectangle(adjustmentX, 2*padding + 4.25*BLOCK_SIZE + CELL_BORDER, scoreDimension - 2*CELL_BORDER, 3*BLOCK_SIZE - 2*CELL_BORDER, SfmlWindow::White);
    window.fillRectangle(adjustmentX, 2.5*padding + 8.25*BLOCK_SIZE + CELL_BORDER, scoreDimension - 2*CELL_BORDER, 3*BLOCK_SIZE - 2*CELL_BORDER, SfmlWindow::White);

    window.drawBigString(adjustmentX + padding, 2*padding + 3*BLOCK_SIZE, "RECORD", textColour);
    window.drawVeryBigString(adjustmentX + 2*padding, 3.5*padding + 3*BLOCK_SIZE, std::to_string(game->getHiScore(boardNumber)), SfmlWindow::Black);

    window.drawBigString(adjustmentX + padding, 2*padding + padding/2 + 7*BLOCK_SIZE, "SCORE", textColour);
    window.drawVeryBigString(adjustmentX + 2*padding, 3.5*padding + padding/2 + 7*BLOCK_SIZE, std::to_string(game->getScore(boardNumber)), SfmlWindow::Black);

}



void GraphicsObserver::notify() {
    setWindowInactive();
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
    run();
    window.display();
}

void GraphicsObserver::run() {
    if (game->getPlayer(1)->isLose()) {
        printLostScreen(1);
        return;
    } else if (game->getPlayer(2)->isLose()) {
        printLostScreen(2);
        return;
    }
    printBoard(game->getBoard(1), game->getBoard(2));
    printScore(1);
    printScore(2);
    printNextBlock(game->getPlayer(1)->getNextBlock(), game->getPlayer(2)->getNextBlock());

    if (!game->getPlayer(1)->isLose() && !game->getPlayer(2)->isLose()) {
        window.fillRectangle(0, SCREEN_HEIGHT - 4*BLOCK_SIZE, SCREEN_WIDTH, 4*BLOCK_SIZE, backgroundColour);
    }
}

