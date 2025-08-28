#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>

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

std::bitset<4> board[8][8] = {
    {WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK},
    {WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN},
    {BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING, BBISHOP, BKNIGHT, BROOK}
};

std::bitset<6> PiecePos[2][16] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
    {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63}
};

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
            std::cout <<  pieceToChar(board[y][x]) << " ";
        }
        std::cout << y+1  << "\n";
    }
    std::cout << "A|B|C|D|E|F|G|H|\n";
}

bool makeMove(const std::string& move) {
    int x1 = move[0] - 'a';
    int y1 = move[1] - '1';
    int x2 = move[2] - 'a';
    int y2 = move[3] - '1';
    if (board[y1][x1].to_ulong() > 0 && (board[y2][x2].to_ulong() % 2 != board[y1][x1].to_ulong() %2 || board[y2][x2].to_ulong() == 0) && board[y1][x1].to_ulong() %2 == turn) {
    	board[y2][x2] = board[y1][x1];
    	board[y1][x1] = 0;
        return true;  
	} else {
        return false;
    }
}

int main() {

	clearScreen();
    printBoard();
	lastMove("");

    turn = false;

    while (true) {
        std::string move;
        std::cin >> move;
        if (!makeMove(move)){
            if (move == "q") {
                break;
            }	
            else {
                clearScreen();
                printBoard();
                std::cout << "Invalid input \n";
                continue;
            }
        }
        turn = !turn;
        clearScreen();
        printBoard();
    }
    
    return 0;
}
