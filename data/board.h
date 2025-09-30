#ifndef board_H
#define board_H

#include <bitset>
#include <vector>
#include <cstdint>

extern std::bitset<4> board[64];

extern std::string LastMove;
void lastMove(const std::string& latestMove);

enum Piece : uint8_t {
    EMPTY = 0,
    WPAWN = 2, BPAWN = 3,
    WROOK = 4, BROOK = 5,
    WKNIGHT = 6, BKNIGHT = 7,
    WBISHOP = 8, BBISHOP = 9,
    WQUEEN = 10, BQUEEN = 11,
    WKING = 12, BKING = 13
};

void setup();

void printBoard();

int IndexFrom2D(int x, int y);

int charToPiece(char c);

extern std::bitset<4> CastelingRights;

#endif
