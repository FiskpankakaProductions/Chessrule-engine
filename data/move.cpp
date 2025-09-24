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
	
	int targetSquare = board[indexTo].to_ulong();
	if (!(board[indexFrom].to_ulong() > 0 && (board[indexTo].to_ulong() % 2 != board[indexFrom].to_ulong() %2 || board[indexTo].to_ulong() == 0) && board[indexFrom].to_ulong() %2 == turn)) {
		return false;
	}

	// int x1 = indexFrom%8, y1 = indexFrom/8, x2 = indexTo%8, y2 = indexTo/8;
	int piece = board[indexFrom].to_ulong();

	bool Legal = false;
	switch(piece) {
		case WPAWN:
			if (move[0] == move[2] && targetSquare == EMPTY) {
				if (move[3] - move[1] == 1) {
					Legal = true;
				} else if (move[1] == '2' && move[3] - move[1] == 2 && board[indexFrom + 8] == EMPTY) {
					Legal = true;
				}
			} else if (abs(move[2] - move[0]) == 1 && move[3]-move[1] == 1 && targetSquare != EMPTY) {
				Legal = true;
			}
			break;
		case BPAWN:
			if (move[2] == move[0] && targetSquare == EMPTY ) {
				if (move[1] - move[3] == 1) {
					Legal = true;
				} else if (move[1] == '7' && move[1] - move[3] == 2 && board[indexFrom - 8] == EMPTY) {
					Legal = true;
				}
			} else if (abs(move[2] - move[0]) == 1 && move[1]-move[3] == 1 && targetSquare != EMPTY) {
				Legal = true;
			}
			break;

		case WROOK: case BROOK:
			if (move[0] == move[2]) {
				int distance = move[1] - move[3];
				int increment = distance/abs(distance);
				Legal = true;
				for (int i = increment; i != distance+1; i+=increment) {	
					if (board[indexFrom + i].to_ulong() != EMPTY) {
						Legal = false;
						break;						
					}
									
				}
			
					
			} else if (move[1] == move[3]) {
				int distance = move[0] - move[2];
				int increment = distance/abs(distance);
				Legal = true;
				for (int i = increment; i != distance+1; i+=increment) {
					if (board[indexFrom + i*8].to_ulong() != EMPTY) {
						Legal = false;
						break;
					}
				}
			}
			break;

		case WKNIGHT: case BKNIGHT:
			if ((abs(move[2]-move[0]) == 2 && abs(move[3]-move[1]) == 1) || (abs(move[2]-move[0]) == 1 && abs(move[3]-move[1]) == 2)) {
				Legal = true;
			}
			break;

		case WBISHOP: case BBISHOP:
			Legal = true;
			break;

		case WQUEEN: case BQUEEN:
			Legal = true;
			break;

		case WKING: case BKING:
			if (abs(move[2]-move[0]) <= 1 && abs(move[3]-move[1]) <= 1) {
				Legal = true;
			}
			break;

		default:
			Legal = false;
			break;		
	}
	return Legal;
}

bool isCheck() {
	return false;
}

bool isCheckmate() {
	return false;
}
