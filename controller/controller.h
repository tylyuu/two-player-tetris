#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <memory>
using namespace std;

#include "trienode.h"
#include "../board/board.h"
#include "../board/game.h"
#include "../display/text.h"
#include "../display/graphic.h"

class Game;

class TextObserver;
class GraphicsObserver;

class TrieNode;
class Controller {
    shared_ptr<Game>game;
    shared_ptr<TextObserver> text;
    shared_ptr<GraphicsObserver> graphic;
    int current;
    int opponent;
    shared_ptr<CommandTrie>commandTrie;
    vector<string> fileCommand;
    void changeTurn();

public:
    Controller();
    ~Controller();
    void play();
    void gameEnd();
};

#endif
