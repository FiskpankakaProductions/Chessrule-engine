#include "data.h"
#include "../main/board.h"

#include <iostream>
#include <string>

bool isLegal (int piece, std::string move) {
	switch(piece) {
		case WPAWN:
		       return true;
		case BPAWN:
			return true;

		case WROOK: case BROOK:
			return true;

		case WKNIGHT: case BKNIGHT:
			return true;

		case WBISHOP: case BBISHOP:
			return true;

		case WQUEEN: case BQUEEN:
			return true;

		case WKING: case BKING:
			return true;		
	}
	return false;
}
