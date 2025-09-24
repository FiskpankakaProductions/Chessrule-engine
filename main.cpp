#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>

#include "data/board.h"
#include "data/move.h"

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void lastMove(std::string latestMove) {
	std::cout << "Last move: " << latestMove << "\n";
}

bool turn;

bool makeMove(const std::string& move) {
    int indexFrom = IndexFrom2D(move[0] - 'a', move[1] - '1');
    int indexTo = IndexFrom2D(move[2] - 'a', move[3] - '1');
    if (board[indexFrom].to_ulong() > 0 && (board[indexTo].to_ulong() % 2 != board[indexFrom].to_ulong() %2 || board[indexTo].to_ulong() == 0) && board[indexFrom].to_ulong() %2 == turn) {
	    if (isLegal(move) == true) {
		board[indexTo] = board[indexFrom];
    	    	board[indexFrom] = 0;
            	return true;
	    } else {
		    return false;
	    }  
    } else {
        return false;
    }
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
