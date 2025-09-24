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

void lastMove(std::string latestMove) {
	std::cout << "Last move: " << latestMove << "\n";
}

int main() {
    setup();
    clearScreen();
    printBoard();
    lastMove("");

	turn = false;    

    while (true) {
        std::string move;
        std::cin >> move;
	if (move == "q") {
                break;
        }
	else if (!makeMove(move)){
                clearScreen();
                printBoard();
                std::cout << "Invalid input \n";
                continue;
        }
        turn = !turn;
        clearScreen();
        printBoard();
	lastMove(move);
    }
    
    return 0;
}
