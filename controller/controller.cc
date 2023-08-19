#include "controller.h"
#include <memory>
#include <termios.h>
#include <unistd.h>
#include <string>


using namespace std;

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68
#define SLASH 47

std::vector<std::string> commands = {"left", "down", "right", "clockwise",
                                     "counterclockwise", "drop", "levelup",
                                     "leveldown", "norandom", "random",
                                     "sequence", "restart", "remap", "hold",
                                     "I", "J", "L", "O", "S", "T", "Z", "blind",
                                     "heavy", "force", "quit", "togglesfx"};

Controller::Controller() {
    game = std::make_shared<Game>();
    text = std::make_shared<TextObserver>(game);
    graphic = std::make_shared<GraphicsObserver>(game);
    commandTrie = std::make_shared<CommandTrie>();
    current = 1;
    opponent = 2;
    for (auto s: commands) {
        commandTrie->addWord(s);
    }
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

string curseGetLine(){
    char c;
    string input;
    while ((c=getch())) {
        if (c == 27) {
            getch(); // Skip the bracket character
            switch (getch()) {
                case KEY_UP:
                    return "clockwise";
                case KEY_DOWN:
                    return "down";
                case KEY_LEFT:
                    return "left";
                case KEY_RIGHT:
                    return "right";
            }
        }
        if (c == 10) return input;
        if (c == 32) return "drop";
        if (c == SLASH) return "counterclock";
        else {
            cout << c;
            input += c;
        }
    }
}

void Controller::changeTurn() {
    current = opponent;
    if (opponent == 1) opponent = 2;
    else opponent = 1;
}

bool canRestart() {
    while (true) {
        cout << "Do you want to restart or quit game?" << endl;
        cout << "Y/N: ";
        string cmd;
        cin >> cmd;
        if (cmd == "Y" || cmd == "y" || cmd == "yes" || cmd == "Yes") return true;
        if (cmd == "N" || cmd == "n" || cmd == "no" || cmd == "No") return false;
        else cout << "invalid command! please try again. " << endl;
    }
}

void Controller::gameEnd() {
    cout << "--------------------------------" << endl;
    cout << "     Thank you for playing!     " << endl;
    cout << "           Score board: " << endl;
    cout << "       Player 1:  " << game->getPlayer(1)->getScore() << "  " << game->getPlayer(1)->getHiScore() << endl;
    cout << "       Player 2:  " << game->getPlayer(2)->getScore() << "  " << game->getPlayer(2)->getHiScore() << endl;
    cout << "--------------------------------" << endl;

}




void Controller::play() {
    game->render();
    string line;
    while (true) {
        if (game->getPlayer(current)->isLose()) {
            game->render();
            if (canRestart()) {
                game->restartGame();
                game->render();
            } else break;
        }

            cout << "Please enter command: " << endl;
            line = curseGetLine();
            if (line.size() == 0) continue;

            string cmd;
            string num;
            if (isdigit(line.at(0))) {
                num.push_back(line.at(0));
                line.erase(0, 1);
            }
            for (char c: line) {
                if (isdigit(c)) num.push_back(c);
                else cmd.push_back(c);
            }
            if (num.length() == 0) num.push_back('1');
            int time = std::stoi(num);
            cmd = commandTrie->getWord(cmd);

            if (time == 0) continue;

            if (cmd == "right" || cmd == "left" || cmd == "down") {
                game->getPlayer(current)->actOnBlock(cmd, time, "move");
                game->render();
            } else if (cmd == "clockwise" || cmd == "counterclockwise") {
                cout << "rotating " << endl; //** delete after
                game->getPlayer(current)->actOnBlock(cmd, time, "rotate");
                game->render();
            } else if (cmd == "drop") {
                for (int i = 0; i < time; i++) {
                    int row = game->getPlayer(current)->dropBlock();
                    if (game->getPlayer(current)->isBlind()) game->getPlayer(current)->resetBlind();
                    game->render();
                    if (row >= 2) {
                        cout << "Clear " << row << " rows!" << endl;
                        cout << "Please choose a special action on your opponent by entering number: " << endl;
                        cout << "1. blind" << endl;
                        cout << "2. heavy" << endl;
                        cout << "3. force" << endl;
                        int action;
                        cin >> action;
                        if (action == 1) {
                            if (!game->getPlayer(opponent)->isBlind()) game->getPlayer(opponent)->resetBlind();
                            game->render();
                        } else if (action == 2) {
                            if (!game->getPlayer(opponent)->isHeavy()) game->getPlayer(opponent)->resetHeavy();
                        } else if (action == 3) {
                            cout << "You would like the change opponent's current block to: " << endl;
                            cout << "choose between I J L O S Z T" << endl;
                            char block;
                            cin >> block;
                            bool canSet = game->getPlayer(opponent)->setCurrentBlock(block);
                            if (!canSet) {
                                cout << "set block fail!" << endl;
                                game->getPlayer(opponent)->setLose();
                                game->render();
                                if (canRestart()) game->restartGame();
                                else {
                                    gameEnd();
                                    break;
                                }
                            }
                        }
                        getline(cin, line);
                    }
                }
                if (game->getPlayer(current)->isLose()) {
                    if (canRestart()) {
                        game->restartGame();
                        game->render();
                    } else {
                        gameEnd();
                        break;
                    }
                    getline(cin, line);
                }
                changeTurn();
            } else if (cmd == "restart") {
                game->restartGame();
                game->render();
            } else if (cmd == "blind") {
                game->getPlayer(current)->resetBlind();
                game->render();
            } else if (cmd == "heavy") {
                game->getPlayer(current)->resetHeavy();
                game->render();
            } else if (cmd == "lose") {
                game->getPlayer(current)->setLose();
                game->render();
                break;
            } else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" || cmd == "Z" || cmd == "T" || cmd == "S") {
                game->getPlayer(current)->setCurrentBlock(cmd[0]);
                game->render();
            } else if (cmd == "quit") {
                gameEnd();
                break;
            } else {
                cout << "invalid command, please try again" << endl;
            }
        }
}

Controller::~Controller() {}
