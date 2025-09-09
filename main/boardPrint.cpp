#include <iostream>

#include "board.h"

int IndexFrom2D(int x, int y) {
    return y * 8 + x;
}

char pieceToChar(std::bitset<4> p) {
    switch(p.to_ulong()) {
        case WPAWN: return 'P'; case BPAWN: return 'p';
        case WROOK: return 'R'; case BROOK: return 'r';
        case WKNIGHT: return 'N'; case BKNIGHT: return 'n';
        case WBISHOP: return 'B'; case BBISHOP: return 'b';
        case WQUEEN: return 'Q'; case BQUEEN: return 'q';
        case WKING: return 'K'; case BKING: return 'k';
        default: return '.';
    }
}


void printBoard() {
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            std::cout << pieceToChar(board[IndexFrom2D(x, y)]) << " ";
        }
        std::cout <<  "|" << (y + 1) << "\n";
    }
    std::cout << "A|B|C|D|E|F|G|H|\n";
}
