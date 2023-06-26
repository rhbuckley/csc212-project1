//
// Created by Richard Buckley on 6/24/23.
//
#include "interface.h"

int main() {
    Interface anInterface;

    anInterface.startUserControl();

    // no need to save here, the program will save after any change

    std::cout << "Good bye!" << std::endl;
}