#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>

#include "data/board.h"
#include "data/move.h"

bool turn;

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void lastMove(const std::string& latestMove) {
    std::cout << "Last move: " << latestMove << "\n";
}

int main() {
    setup();
    turn = false;
    std::string LastMove = "";
    while (true) {
        clearScreen();
        printBoard();
        lastMove(LastMove);

        std::string move;
        std::getline(std::cin, move);

        if (move.empty()) continue;
        if (move == "q") break;

       if (!makeMove(move)) {
            std::cout << "Invalid input. Press Enter to continue...\n";
            std::cin.get();
            continue;
       }
        LastMove = move;
        turn = !turn;
    }

    return 0;
}
