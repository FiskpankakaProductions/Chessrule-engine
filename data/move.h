#ifndef move_H
#define move_H

#include <string>

extern bool turn;

bool makeMove(const std::string& move);
bool isLegal (std::string move);
bool isCheck();
bool isCheckmate();

#endif
