#include <vector>
using namespace std;

#include "subject.h"

void Subject::notifyObservers() const {
    for (auto &ob : observers) ob->notify();
}

void Subject::attach(Observer* ob) {
    observers.emplace_back(ob);
}

void Subject::detach(Observer* ob) {
    for (auto it = observers.begin(); it != observers.end(); ) {
        if (*it == ob) it = observers.erase(it);
        else ++it;
    }
}
