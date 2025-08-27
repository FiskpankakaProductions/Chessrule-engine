#include <iostream>
#include <bitset>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

std::bitset<4> board[8][8] = {
    {8, 4, 6, 10, 12, 6, 4, 8},
    {2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {3, 3, 3, 3, 3, 3, 3, 3},
    {9, 5, 7, 11, 13, 7, 5, 9}
};

void printBoard() {
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < 8; col++) {
            std::cout <<  board[row][col] << " ";
        }
        std::cout << "\n";
    }
}

void makeMove(const std::string& move) {
    int x1 = move[0] - '0' - 1;
    int y1 = move[1] - '0' - 1;
    int x2 = move[2] - '0' - 1;
    int y2 = move[3] - '0' - 1;
    board[y2][x2] = board[y1][x1];
    board[y1][x1] = 0;
}

int main() {
	clearScreen();
    	printBoard();
    while (true) {
        std::string move;
        std::cin >> move;
        if (move.length() == 4) {
            makeMove(move);
	    clearScreen();
            printBoard();
	}
	else if (move == "q") {
		break;
        }
	else {
		std::cout << "Invalid input";
	}
    }
    
    return 0;
}
