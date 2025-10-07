#include <iostream>
#include <fstream>
#include <string>

#include "board.h"

void sendBoard() {
	std::ofstream outFile("board.txt");

	for (int i = 0; i < 64; i++) {
        	outFile << board[i].to_ulong() << " ";
        	if ((i + 1) % 8 == 0) outFile << "\n";
    	}	
}
