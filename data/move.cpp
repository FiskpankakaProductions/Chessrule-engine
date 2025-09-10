#include "move.h"
#include "board.h"

#include <iostream>
#include <string>
#include <bitset>

bool isLegal (std::string move) {
	
	int indexFrom = IndexFrom2D(move[0] - 'a', move[1] - '1');
    int indexTo = IndexFrom2D(move[2] - 'a', move[3] - '1');

	
	int piece = board[indexFrom].to_ulong();
	switch(piece) {
		case WPAWN:
			if (move[3] - move[1] == 1) {
				return true;
			} else {
				return false;
			}
		case BPAWN:
			if (move[3] - move[1] == -1) {
				return true;
			} else {
				return false;
			}

		case WROOK: case BROOK:
			return true;

		case WKNIGHT: case BKNIGHT:
			return true;

		case WBISHOP: case BBISHOP:
			return true;

		case WQUEEN: case BQUEEN:
			return true;

		case WKING: case BKING:
			if (abs(move[0] - move[2]) == 1 || abs(move[1] - move[3]) == 1) {
				return true;
			} else {
				return false;
			}

		default:
			return false;		
	}
	
}
bool isCheck() {
	return false;
}
