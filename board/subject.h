#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
using namespace std;

#include "../display/observer.h"

class Subject {
    vector<Observer*> observers;

public:
    virtual ~Subject() = default;
    void notifyObservers() const;
    void attach(Observer* ob);
    void detach(Observer* ob);
};

#endif
