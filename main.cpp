#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>

#include "data/board.h"
#include "data/move.h"
#include "data/sendData.h"

bool turn;

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

int main() {
    setup();
    sendBoard();
    turn = false;
    LastMove = "";
    while (true) {
        clearScreen();
        printBoard();
        if (isCheck()) {
            std::cout << "Check!\n";
        }
        lastMove(LastMove);

        std::string move;
        std::getline(std::cin, move);

        if (move.empty()) continue;
        if (move == "q") break;
	if (move == "50") {
		if (MoveSinceLastCaptureOrPawnMove => 100) {
			std::cout << "Draw by Fifty-move rule\n";
			break;	
		} 
	}

       if (!makeMove(move)) {
            std::cout << "Invalid input. Press Enter to continue...\n";
            std::cin.get();
            continue;
       }
        LastMove = move;
        turn = !turn;
	    sendBoard();
        if (hasLegalMoves()) {
            if (isCheck()) {
                clearScreen();
                printBoard();
                std::cout << "Checkmate! " << (turn ? "White" : "Black") << " wins!\n";
                break;
            } else {
                clearScreen();
                printBoard();
                std::cout << "Stalemate! It's a draw!\n";
                break;
            }
        }
    }

    return 0;
}
