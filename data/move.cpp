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

bool isLegal(int& indexFrom, int& indexTo, const std::string& move) {
	// Jag la till detta för tillfället, det kommer behövas ändras med promotions och casteling.
    if (move.size() != 4) return false;
	if (move[0] < 'a' || move[0] > 'h') return false;
	if (move[2] < 'a' || move[2] > 'h') return false;
	if (move[1] < '1' || move[1] > '8') return false;
	if (move[3] < '1' || move[3] > '8') return false;


	int targetSquare = board[indexTo].to_ulong();
	int piece = board[indexFrom].to_ulong();


	if (!(piece > 0 && (targetSquare % 2 != piece % 2 || targetSquare == EMPTY) && piece % 2 == turn)) return false;

    bool Legal = false;
    int x1 = indexFrom % 8, y1 = indexFrom / 8;
    int x2 = indexTo % 8, y2 = indexTo / 8;

    switch (piece) {
        case WPAWN:
            if (x1 == x2 && targetSquare == EMPTY) {
                if (y2 - y1 == 1) Legal = true;
                else if (y1 == 1 && y2 - y1 == 2 && board[indexFrom + 8] == EMPTY) Legal = true;
            } else if (abs(x2 - x1) == 1 && y2 - y1 == 1 && targetSquare != EMPTY) {
                Legal = true;
            }
            break;

        case BPAWN:
            if (x1 == x2 && targetSquare == EMPTY) {
                if (y1 - y2 == 1) Legal = true;
                else if (y1 == 6 && y1 - y2 == 2 && board[indexFrom - 8] == EMPTY) Legal = true;
            } else if (abs(x2 - x1) == 1 && y1 - y2 == 1 && targetSquare != EMPTY) {
                Legal = true;
            }
            break;

        case WROOK: case BROOK:
            if (x1 == x2) {
                int step = (y2 > y1) ? 8 : -8;
                for (int pos = indexFrom + step; pos != indexTo; pos += step) {
                    if (board[pos].to_ulong() != EMPTY) return false;
                }
                Legal = true;
            } else if (y1 == y2) {
                int step = (x2 > x1) ? 1 : -1;
                for (int pos = indexFrom + step; pos != indexTo; pos += step) {
                    if (board[pos].to_ulong() != EMPTY) return false;
                }
                Legal = true;
            }
            break;

        case WKNIGHT: case BKNIGHT:
            if ((abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2)) {
                Legal = true;
            }
            break;

        case WBISHOP: case BBISHOP:
            if (abs(x2 - x1) == abs(y2 - y1)) {
                int stepX = (x2 > x1) ? 1 : -1;
                int stepY = (y2 > y1) ? 8 : -8;
                int step = stepX + stepY;
                for (int pos = indexFrom + step; pos != indexTo; pos += step) {
                    if (board[pos].to_ulong() != EMPTY) return false;
                }
                Legal = true;
            }
            break;

        case WQUEEN: case BQUEEN:
            if (x1 == x2) {
                int step = (y2 > y1) ? 8 : -8;
                for (int pos = indexFrom + step; pos != indexTo; pos += step) {
                    if (board[pos].to_ulong() != EMPTY) return false;
                }
                Legal = true;
            } else if (y1 == y2) {
                int step = (x2 > x1) ? 1 : -1;
                for (int pos = indexFrom + step; pos != indexTo; pos += step) {
                    if (board[pos].to_ulong() != EMPTY) return false;
                }
                Legal = true;
            } else if (abs(x2 - x1) == abs(y2 - y1)) {
                int stepX = (x2 > x1) ? 1 : -1;
                int stepY = (y2 > y1) ? 8 : -8;
                int step = stepX + stepY;
                for (int pos = indexFrom + step; pos != indexTo; pos += step) {
                    if (board[pos].to_ulong() != EMPTY) return false;
                }
                Legal = true;
            }
            break;

        case WKING: case BKING:
            if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) {
                Legal = true;
            }
            break;

        default:
            Legal = false;
            break;
    }
	if (!Legal) return false;

    int toSquareOldPiece = board[indexTo].to_ulong();
    board[indexTo] = board[indexFrom];
    board[indexFrom] = EMPTY;

    bool kingInCheck = isCheck();

    board[indexFrom] = board[indexTo];
    board[indexTo] = toSquareOldPiece;

    if (kingInCheck) return false;

    return true;
}

int FindKing() {
	for (int i = 0; i < 64; i++) {
		if (board[i].to_ulong() == (turn == false ? WKING : BKING)) {
			return i;
		}
	}
	return -1;
}


bool isCheck() {
    int kingPos = FindKing();
    if (kingPos == -1) return false;

    int x = kingPos % 8;
    int y = kingPos / 8;

    int knightMoves[8][2] = {{1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}};
    for (auto& m : knightMoves) {
        int nx = x + m[0], ny = y + m[1];
        if (nx>=0 && nx<8 && ny>=0 && ny<8) {
            int p = board[ny*8+nx].to_ulong();
            if (p == (turn ? WKNIGHT : BKNIGHT)) return true;
        }
    }

    int pawnDir = (turn==0) ? 1 : -1;
    int pawnRow = y + pawnDir;
    if (pawnRow>=0 && pawnRow<8) {
        if (x>0) {
            int p = board[pawnRow*8+(x-1)].to_ulong();
            if (p == (turn ? WPAWN : BPAWN)) return true;
        }
        if (x<7) {
            int p = board[pawnRow*8+(x+1)].to_ulong();
            if (p == (turn ? WPAWN : BPAWN)) return true;
        }
    }


    const int rookDirections[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for (auto& d : rookDirections) {
        int nx = x, ny = y;
        while (true) {
            nx += d[0]; ny += d[1];
            if (nx<0 || nx>7 || ny<0 || ny>7) break;
            int p = board[ny*8+nx].to_ulong();
            if (p != EMPTY) {
                if (p == (turn ? WROOK : BROOK) || p == (turn ? WQUEEN : BQUEEN))
                    return true;
                break;
            }
        }
    }

    const int bishopDirections[4][2] = {{1,1},{-1,1},{1,-1},{-1,-1}};
    for (auto& d : bishopDirections) {
        int nx = x, ny = y;
        while (true) {
            nx += d[0]; ny += d[1];
            if (nx<0 || nx>7 || ny<0 || ny>7) break;
            int p = board[ny*8+nx].to_ulong();
            if (p != EMPTY) {
                if (p == (turn ? WBISHOP : BBISHOP) || p == (turn ? WQUEEN : BQUEEN))
                    return true;
                break;
            }
        }
    }

    for (int dx=-1; dx<=1; dx++) {
        for (int dy=-1; dy<=1; dy++) {
            if (dx==0 && dy==0) continue;
            int nx = x+dx, ny = y+dy;
            if (nx>=0 && nx<8 && ny>=0 && ny<8) {
                int p = board[ny*8+nx].to_ulong();
                if (p == (turn ? WKING : BKING)) return true;
            }
        }
    }

    return false;
}

bool isCheckmate() {
	return false;
}
