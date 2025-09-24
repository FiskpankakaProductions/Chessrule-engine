#include "move.h"
#include "board.h"

#include <iostream>
#include <string>
#include <bitset>

bool makeMove(const std::string& move) {
	int indexFrom = IndexFrom2D(move[0] - 'a', move[1] - '1');
    int indexTo = IndexFrom2D(move[2] - 'a', move[3] - '1');
	if (!isLegal(indexFrom, indexTo, move)) {
		return false;
	} else {
		board[indexTo] = board[indexFrom];
		board[indexFrom] = EMPTY;
		return true;
	}
}

bool isLegal (int& indexFrom, int& indexTo, const std::string& move) {
	

	if (!(board[indexFrom].to_ulong() > 0 && (board[indexTo].to_ulong() % 2 != board[indexFrom].to_ulong() %2 || board[indexTo].to_ulong() == 0) && board[indexFrom].to_ulong() %2 == turn)) {
		return false;
	}

	// int x1 = indexFrom%8, y1 = indexFrom/8, x2 = indexTo%8, y2 = indexTo/8;
	int piece = board[indexFrom].to_ulong();
	switch(piece) {
		case WPAWN:
			if (move[1] == '2'){
				if (move[3] - move[1] < 3 && move[0] == move[2]){
					return true;
				}
			} else {
				if (move[3] - move[1] == 1 && (move[0] == move[2]+1 || move[0] == move[2]-1 && (indexTo%2 != 0))) {
					
				} else if (move[3] - move[1] == 1 && move[0] == move[2]) {
					return true;
				} else {
					return false;
				}
			}
				
		case BPAWN:
			if (move[1] == '7'){
				if (move[3] - move[1] > -3 && move[0] == move[2]){
					return true;
				}
			} else {
				if (move[3] - move[1] == -1 && move[0] == move[2]) {
					return true;
				} else {
					return false;
				}
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

bool isCheckmate() {
	return false;
}
