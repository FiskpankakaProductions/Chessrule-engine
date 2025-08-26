#include <iostream>
#include <bitset>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

int main(){

	clearScreen();

	std::bitset<4> board[8][8] =  {
		{8, 4, 6, 10, 12, 6, 4, 8},
		{2, 2, 2, 2, 2, 2, 2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{3, 3, 3, 3, 3, 3, 3, 3},
		{9, 5, 7, 11, 13, 7, 5, 9}
	};

	for (int row = 0; row < 8; row++) {
        	for (int col = 0; col < 8; col++) {
            		std::cout << board[row][col] << " ";
        	}
        	std::cout << "\n";
    	}

	return 0;
}
