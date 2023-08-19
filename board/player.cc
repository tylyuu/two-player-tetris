#include <string>
#include "player.h"
#include <memory>
#include <memory>
#include <iostream>
using namespace std;

Player::Player(const std::shared_ptr<Board>board, int hiScore) : board{board}, highScore{hiScore},
                                                                  blind{false}, force{false} {
    generator= make_shared<Generator>();
    currentBlock = generateBlock();
    nextBlock = generateBlock();
    initBlock();
}

int Player::getScore() const {
    return curScore;
}

int Player::getHiScore() const {
    return highScore;
}


char Player::getCurrentBlock() const {
    return currentBlock;
}

char Player::getNextBlock() const {
    return nextBlock;
}

void Player::updateScore(int numRows) {
    if (numRows > 0) {
        curScore += numRows;
        if (curScore > highScore) highScore = curScore;
    }
}



bool Player::setCurrentBlock(char block) {
    bool canSet = board->setCurrentBlock(block);
    if (canSet) currentBlock = block;
    return canSet;
}

void Player::setNextBlock(char block) {
    nextBlock = block;
}


void Player::actOnBlock(const std::string& direction, int magnitude, const std::string&& action) const {
    for (int i = 0; i < magnitude; i++){
        if (board->actionDone(action)) break;
        else board->actionBlock(direction, action);
    }
    if (heavy && direction!="down") {
        board->actionBlock("down","move");
        board->actionBlock("down","move");
    }
    board->resetAction(action);

}

void Player::resetHeavy(){
    heavy = !heavy;
}

void Player::resetBlind() {
    blind = !blind;
    board->resetBlind();
}

void Player::setLose() {
    lose = !lose;
}

bool Player::isBlind() const {
    return blind;
}

bool Player::isHeavy() const {
    return heavy;
}

bool Player::isLose() const {
    return lose;
}

void Player::initBlock() {
    if (board->canSpecial()){
        currentBlock = 'F';
        board->initBlock(currentBlock);
        dropBlock();
        board->resetSpecial();
    }
    currentBlock = nextBlock;
    if (board->initBlock(currentBlock)) {
        nextBlock = generateBlock();
    } else {
        lose = true;
    }
}

int Player::dropBlock() {
    if (!board->dropBlock()) lose = true;

    board->resetAction("move");

    int rowClear = board->clearRow();
    updateScore(rowClear);

    initBlock();
    if (rowClear != 0 ) board->resetSpecial();
    return rowClear;
}

char Player::generateBlock() const {
    return generator->next();
}

Player::~Player() {}
