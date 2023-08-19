#ifndef GAME_H
#define GAME_H

#include <memory>

#include "subject.h"
#include "player.h"
#include "board.h"

class Board;
class Player;

class Game: public Subject{
protected:
    vector<std::shared_ptr<Player>> players;
    vector<std::shared_ptr<Board>> boards;

public:
    Game();
    void render() const;
    void restartGame();
    void initBoard();
    void switchPlayer();
    void forceOpponent(char block);
    int getScore(int which) const;
    int getHiScore(int which) const;
    std::shared_ptr<Player> getPlayer(int which) const ;
    std::shared_ptr<Board> getBoard(int which) const ;
    ~Game();
};

#endif
