#include "move.h"
#include "board.h"

#include <iostream>
#include <string>
#include <bitset>

int FindKing() {
	for (int i = 0; i < 64; i++) {
		if (board[i].to_ulong() == (turn == false ? WKING : BKING)) {
			return i;
		}
	}
	return -1;
}

bool makeMove(const std::string& move) {
    if (move == "O-O" || move == "O-O-O") {
        if (isCheck()) return false;
        if (move == "O-O" && (turn ? CastelingRights[2] : CastelingRights[0])) {
            int kingindex = FindKing();
            if (kingindex == -1) return false;
            if (board[kingindex + 1].to_ulong() != EMPTY || board[kingindex+2].to_ulong() != EMPTY) return false;
            board[kingindex + 1] = board[kingindex];
            board[kingindex] = EMPTY;
            if (isCheck()) {
                board[kingindex] = board[kingindex + 1];
                board[kingindex + 1] = EMPTY;
                return false;
            }
            board[kingindex + 2] = board[kingindex + 1];
            board[kingindex + 1] = EMPTY;
            if (isCheck()) {
                board[kingindex] = board[kingindex + 2];
                board[kingindex + 2] = EMPTY;
                return false;
            }
            board[kingindex + 1] = board[kingindex+3];
            board[kingindex + 3] = EMPTY;
        } else if (move == "O-O-O" && (turn ? CastelingRights[3] : CastelingRights[1])) {
            int kingindex = FindKing();
            if (kingindex == -1) return false;
            if (board[kingindex - 1].to_ulong() != EMPTY || board[kingindex-2].to_ulong() != EMPTY) return false;
            board[kingindex - 1] = board[kingindex];
            board[kingindex] = EMPTY;
            if (isCheck()) {
                board[kingindex] = board[kingindex - 1];
                board[kingindex - 1] = EMPTY;
                return false;
            }
            board[kingindex - 2] = board[kingindex - 1];
            board[kingindex - 1] = EMPTY;
            if (isCheck()) {
                board[kingindex] = board[kingindex - 2];
                board[kingindex - 2] = EMPTY;
                return false;
            }
            board[kingindex - 1] = board[kingindex-4];
            board[kingindex - 4] = EMPTY; 
        }
        if (turn) { CastelingRights[2] = CastelingRights[3] = false; }
        else { CastelingRights[0] = CastelingRights[1] = false; }
        return true;
    }

    int indexFrom = IndexFrom2D(move[0] - 'a', move[1] - '1');
    int indexTo = IndexFrom2D(move[2] - 'a', move[3] - '1');

	if (!isLegal(indexFrom, indexTo, move)) {
		return false;
	} else {
		board[indexTo] = board[indexFrom];
		board[indexFrom] = EMPTY;

        int piece = board[indexTo].to_ulong();

        if (move.size() == 5 && piece == (turn ? BPAWN : WPAWN)) board[indexTo] = charToPiece(move[4]) + (turn ? 1 : 0);
        if (piece == WROOK) {
            if (indexTo%8 == 0) CastelingRights[0] = false;
            if (indexTo%8 == 7) CastelingRights[1] = false;
        }
        if (piece == BROOK) {
            if (indexTo%8 == 0) CastelingRights[2] = false;
            if (indexTo%8 == 7) CastelingRights[3] = false;
        }
        if (piece == WKING) { CastelingRights[0] = CastelingRights[1] = false; }
        if (piece == BKING) { CastelingRights[2] = CastelingRights[3] = false; }
        

		return true;
	}
}

bool isLegal(int& indexFrom, int& indexTo, const std::string& move) {
    if (move.size() != 4 && move.size() != 5) return false;
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
            } else if (y2 == 5 && abs(x2-x1) == 1 && y2 - y1 == 1 && targetSquare == EMPTY) {
                if (board[indexTo - 8].to_ulong() == BPAWN && indexTo - 8 == IndexFrom2D(LastMove[2] - 'a', LastMove[3] - '1')) {
                    auto temp = board[indexTo - 8];
                    board[indexTo - 8] = EMPTY;
                    board[indexTo] = board[indexFrom];
                    board[indexFrom] = EMPTY;
                    bool KinginCheck = isCheck();
                    board[indexFrom] = board[indexTo];
                    board[indexTo] = EMPTY;
                    if (!KinginCheck) {
                        return true;
                    } else {
                        board[indexTo - 8] = temp;
                        return false;
                    }
                }
            }
            if (y2 == 7) {
                if (move.size() != 5) Legal = false;
                else if (move[4] != 'Q' && move[4] != 'R' && move[4] != 'B' && move[4] != 'N') Legal = false;;
            }
            break;

        case BPAWN:
            if (x1 == x2 && targetSquare == EMPTY) {
                if (y1 - y2 == 1) Legal = true;
                else if (y1 == 6 && y1 - y2 == 2 && board[indexFrom - 8] == EMPTY) Legal = true;
            } else if (abs(x2 - x1) == 1 && y1 - y2 == 1 && targetSquare != EMPTY) {
                Legal = true;
            } else if (y2 == 2 && abs(x2-x1) == 1 && y1 - y2 == 1 && targetSquare == EMPTY) {
                if (board[indexTo + 8].to_ulong() == WPAWN && indexTo + 8 == IndexFrom2D(LastMove[2] - 'a', LastMove[3] - '1')) {
                    auto temp = board[indexTo + 8];
                    board[indexTo + 8] = EMPTY;
                    board[indexTo] = board[indexFrom];
                    board[indexFrom] = EMPTY;
                    bool KinginCheck = isCheck();
                    board[indexFrom] = board[indexTo];
                    board[indexTo] = EMPTY;
                    if (!KinginCheck) {
                        return true;
                    } else {
                        board[indexTo + 8] = temp;
                        return false;
                    }
                }
            }
            if (y2 == 0) {
                if (move.size() != 5) Legal = false;
                else if (move[4] != 'Q' && move[4] != 'R' && move[4] != 'B' && move[4] != 'N') Legal = false;;
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
    for (int from = 0; from < 64; from++) {
        int piece = board[from].to_ulong();

        if (piece == EMPTY || piece % 2 != turn) continue;

        for (int to = 0; to < 64; to++) {
            if (from == to) continue;

            int target = board[to].to_ulong();
            if (target != EMPTY && target % 2 == turn) continue;

            std::string move = "";
            move += ('a' + (from % 8));
            move += ('1' + (from / 8));
            move += ('a' + (to % 8));
            move += ('1' + (to / 8));

            if (isLegal(from, to, move)) {
                return false;
            }
        }
    }
    return true;
}

