#ifndef move_H
#define move_H

#include <string>

extern bool turn;

bool makeMove(std::string& move);
int isLegal (int& indexFrom, int& indexTo, const std::string& move);
bool isCheck();
bool hasLegalMoves();

#endif
