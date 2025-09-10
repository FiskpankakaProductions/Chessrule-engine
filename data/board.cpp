#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>

#include "board.h"



std::bitset<4> setupBoard[64] = {
    WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK,
    WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN,
    BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING, BBISHOP, BKNIGHT, BROOK
};


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

//std::vector<std::bitset<6>> PiecesPosistions[2];

std::bitset<4> board[64];
void setup() {
    for (int i = 0; i < 64; i++) {
        board[i] = setupBoard[i];
    }
    /*PiecesPosistions[0].clear();
    PiecesPosistions[1].clear();
    for (int i = 0; i < 16; i++) {
        PiecesPosistions[0].push_back(std::bitset<6>(i)); // White pieces
        PiecesPosistions[1].push_back(std::bitset<6>(i + 48)); // Black pieces
    }*/
}


