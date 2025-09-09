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

std::vector<std::bitset<6>> PiecesPosistions[2];

std::bitset<4> board[64];
void setup() {
    for (int i = 0; i < 64; i++) {
        board[i] = setupBoard[i];
    }
    PiecesPosistions[0].clear();
    PiecesPosistions[1].clear();
    for (int i = 0; i < 16; i++) {
        PiecesPosistions[0].push_back(std::bitset<6>(i)); // White pieces
        PiecesPosistions[1].push_back(std::bitset<6>(i + 48)); // Black pieces
    }
}


