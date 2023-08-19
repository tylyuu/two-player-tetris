#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
using namespace std;

#include "controller/controller.h"

int main() {
    shared_ptr<Controller> c = make_shared<Controller>();
    c->play();
    return 0;
}