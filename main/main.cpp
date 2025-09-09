#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>

#include "../data/data.h"

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void lastMove(std::string latestMove) {
	std::cout << "Last move: " << latestMove << "\n";
}

bool turn;

enum Piece : uint8_t {
    EMPTY = 0,
    WPAWN = 2, BPAWN = 3,
    WROOK = 4, BROOK = 5,
    WKNIGHT = 6, BKNIGHT = 7,
    WBISHOP = 8, BBISHOP = 9,
    WQUEEN = 10, BQUEEN = 11,
    WKING = 12, BKING = 13
};

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

int IndexFrom2D(int x, int y) {
    return y * 8 + x;
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

void GetPieceMoves(std::vector<uint16_t> &Moves) {

}

void GetLegalMoves(std::vector<uint16_t> &Moves) {

}

bool makeMove(const std::string& move) {
    int indexFrom = IndexFrom2D(move[0] - 'a', move[1] - '1');
    int indexTo = IndexFrom2D(move[2] - 'a', move[3] - '1');
    if (board[indexFrom].to_ulong() > 0 && (board[indexTo].to_ulong() % 2 != board[indexFrom].to_ulong() %2 || board[indexTo].to_ulong() == 0) && board[indexFrom].to_ulong() %2 == turn) {
    	board[indexTo] = board[indexFrom];
    	board[indexFrom] = 0;
        return true;  
	} else {
        return false;
    }
}

int main() {
    setup();
	clearScreen();
    printBoard();
	lastMove("");

    turn = false;

    while (true) {
        std::string move;
        std::cin >> move;
	if (move == "q") {
                break;
        }
	else if (!makeMove(move)){
                clearScreen();
                printBoard();
                std::cout << "Invalid input \n";
                continue;
        }
        turn = !turn;
        clearScreen();
        printBoard();
	lastMove(move);
    }
    
    return 0;
}
