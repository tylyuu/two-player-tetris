#include <memory>
#include <iostream>

#include "game.h"

using namespace std;


Game::Game(){
    initBoard();
}

Game::~Game() {}

void Game::initBoard() {
    std::shared_ptr<Board> firstBoard = std::make_shared<Board>();
    std::shared_ptr<Board>secondBoard = std::make_shared<Board>();
    std::shared_ptr<Player>firstPlayer = std::make_shared<Player>(firstBoard, 0);
    std::shared_ptr<Player>secondPlayer = std::make_shared<Player>(secondBoard, 0);
    boards.emplace_back(firstBoard);
    boards.emplace_back(secondBoard);
    players.emplace_back(firstPlayer);
    players.emplace_back(secondPlayer);
}

void Game::restartGame() {
    int firstScore = players[0]->getHiScore();
    int secondScore = players[1]->getHiScore();
    boards.pop_back();
    boards.pop_back();
    players.pop_back();
    players.pop_back();
    std::shared_ptr<Board>firstBoard = std::make_shared<Board>();
    std::shared_ptr<Board>secondBoard = std::make_shared<Board>();
    std::shared_ptr<Player>firstPlayer = std::make_shared<Player>(firstBoard, firstScore);
    std::shared_ptr<Player>secondPlayer = std::make_shared<Player>(secondBoard, secondScore);
    boards.emplace_back(firstBoard);
    boards.emplace_back(secondBoard);
    players.emplace_back(firstPlayer);
    players.emplace_back(secondPlayer);
}

void Game::render() const {
    notifyObservers();
}




int Game::getScore(int which) const {
    return players[which-1]->getScore();
}

int Game::getHiScore(int which) const {
    return players[which-1]->getHiScore();
}

std::shared_ptr<Player> Game::getPlayer(int which) const {
    return players[which-1];
}

std::shared_ptr<Board> Game::getBoard(int which) const {
    return boards[which-1];
}

