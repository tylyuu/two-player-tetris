#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../blocks/block.h"
#include "generator.h"
#include <memory>
#include "board.h"

class Board;
class Block;

class Player {

protected:
    std::shared_ptr<Board>board;
    std::shared_ptr<Generator>generator;
    char currentBlock;
    char nextBlock;
    int curScore = 0;
    int highScore;
    bool heavy = false;
    bool blind = false;
    bool force = false;
    bool lose = false;

public:
    Player(const std::shared_ptr<Board>board, int hiScore);
    int getScore() const ;
    int getHiScore() const ;
    char getCurrentBlock() const ;
    char getNextBlock() const ;
    char generateBlock() const ;
    void initBlock();
    void updateScore(int numRows);
    void setRandom(bool ran);
    bool setCurrentBlock(char block);
    void setNextBlock(char block);
    void resetHeavy();
    void resetBlind();
    void setLose();
    bool isBlind() const;
    bool isHeavy() const;
    bool isLose() const;
    void actOnBlock(const std::string& direction, int distance, const std::string&& action) const;
    int dropBlock();
    ~Player();
};

#endif
