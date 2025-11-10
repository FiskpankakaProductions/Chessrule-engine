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

std::bitset<4> CastelingRights = 0b1111;

std::string LastMove = "";

int MoveSinceLastCaptureOrPawnMove = 0;

void lastMove(const std::string& latestMove) {
    std::cout << "Last move: " << latestMove << "\n";
}


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

int charToPiece(char c) {
    switch(c) {
        case 'P': return WPAWN; case 'p': return BPAWN;
        case 'R': return WROOK; case 'r': return BROOK;
        case 'N': return WKNIGHT; case 'n': return BKNIGHT;
        case 'B': return WBISHOP; case 'b': return BBISHOP;
        case 'Q': return WQUEEN; case 'q': return BQUEEN;
        case 'K': return WKING; case 'k': return BKING;
        default: return EMPTY;
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

std::bitset<4> board[64];
void setup() {
    for (int i = 0; i < 64; i++) {
        board[i] = setupBoard[i];
    }
}
std::vector<int> HashTable;
std::vector<int> HashTableRepetitions;

extern bool turn;
bool AddToHashTable() {
    int hash = 0;
    for (int i = 0; i < 64; i++) {
        hash ^= ((board[i].to_ulong()+1) * (i + 1))*3;
    }
    hash ^= CastelingRights.to_ulong() * 7;
    hash ^= turn ? 5 : 11;
    bool found = false;
    for (int i = 0; i < HashTable.size(); i++) {
        if (HashTable[i] == hash) {
            found = true;
            HashTableRepetitions[i]++;
            return HashTableRepetitions[i] == 3;
        }
    }
    if (!found) {
        HashTable.push_back(hash);
        HashTableRepetitions.push_back(1);
    }
    return false;
}

void ClearPositionHashTable() {
    HashTable.clear();
    HashTableRepetitions.clear();
}