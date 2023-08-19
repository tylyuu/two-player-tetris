#include "text.h"

using namespace std;

TextObserver::TextObserver(std::shared_ptr<Game> game): game{game}{
    game->attach(this);
}

TextObserver::~TextObserver() {
    game->detach(this);
} 

void TextObserver::displayDivider() {
    for (int i = 0; i < NUM_COLS; i++){
        cout << "-";
    }
    for (int i = 0; i < NUM_COLS; i++){
        cout << " ";
    }
    for (int i = 0; i < NUM_COLS; i++){
        cout << "-";
    }
    cout << endl;
}

void TextObserver::printBoard(std::shared_ptr<Board> firstBoard, std::shared_ptr<Board> secondBoard) { 
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS * 3; j++)
        {
            if (j < NUM_COLS)
                cout << firstBoard->getState(i, j);
            else if (j >= NUM_COLS * 2)
                cout << secondBoard->getState(i, j - NUM_COLS * 2);
            else
                cout << " ";
        }
        cout << endl;
    }
    displayDivider();
}

void TextObserver::printNextBlockTop(char block) {
    if (block == 'I') {
        cout << "           ";
    } else if (block == 'J') {
        cout << "J          ";
    } else if (block == 'L') {
        cout << "  L        ";
    } else if (block == 'O') {
        cout << "OO         ";
    } else if (block == 'S') {
        cout << " SS        ";
    } else if (block == 'T') {
        cout << "TTT        ";
    } else { // if (currBlock == 'Z') {
        cout << "ZZ        ";
    }
}

void TextObserver::printNextBlockBottom(char block) {
    if (block == 'I') {
        cout << "IIII       ";
    } else if (block == 'J') {
        cout << "JJJ        ";
    } else if (block == 'L') {
        cout << "LLL        ";
    } else if (block == 'O') {
        cout << "OO         ";
    } else if (block == 'S') {
        cout << "SS         ";
    } else if (block == 'T') {
        cout << " T         ";
    } else { // if (currBlock == 'Z') {
        cout << " ZZ        ";
    }
};

void TextObserver::printNextBlock(char firstBlock, char secondBlock) {
    printNextBlockTop(firstBlock);
    cout << "           ";
    printNextBlockTop(secondBlock);
    cout << endl;
    printNextBlockBottom(firstBlock);
    cout << "           ";
    printNextBlockBottom(secondBlock);
}

void TextObserver::printLostScreen(int index) {
    cout<<"-----------------------------------"<<endl;
    cout << "           "<<"Player "<<index<<" lost"<<endl;
    cout<<"-----------------------------------"<<endl;
}

void TextObserver::notify() {
    cout << endl;
    if (game->getPlayer(1)->isLose()) {
        printLostScreen(1);
    } else if (game->getPlayer(2)->isLose()) {
        printLostScreen(2);
    }
    cout << "  Player1               Player2 " <<endl;
    displayDivider();
    cout << "Score:    " << game->getScore(1);
    for (int i = 0; i < NUM_COLS; i++){
        cout << " ";
    }
    cout << "Score:    " << game->getScore(2);
    cout << endl;
    cout << "Record:   " << game->getHiScore(1);
    for (int i = 0; i < NUM_COLS; i++){
        cout << " ";
    }
    cout << "Record:   " << game->getHiScore(2);
    cout << endl;
    displayDivider();

    printBoard(game->getBoard(1), game->getBoard(2));

    cout << "Next:     " ;
    for (int i = 0; i < NUM_COLS; i++){
        cout << " ";
    }
    cout << "Next:     " <<endl;
    printNextBlock(game->getPlayer(1)->getNextBlock(), game->getPlayer(2)->getNextBlock());

    cout << endl;
}
