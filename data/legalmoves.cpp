#include "data.h"

#include <iostream>
#include <string>

bool isLegal (int pice, std::string move) {
	if (pice % 2 == 0) {
		if (pice == 2) {
			isCheck();
		}
		else if (pice == 4) {
			isCheck();
		}
		else if (pice == 6) {
			isCheck();
		}
		else if (pice == 8) {
			isCheck();
		}
		else if (pice == 10) {
			isCheck();
		}
		else if (pice == 12) {
			isCheck();
		}
	}
	else {
		if (pice == 3) {
			isCheck();
		}
		else if (pice == 5) {
			isCheck();
		}
		else if (pice == 7) {
			isCheck();
		}
		else if (pice == 9) {
			isCheck();
		}
		else if (pice == 11) {
			isCheck();
		}
		else if (pice == 13) {
			isCheck();
		}
	}	
return false;
}
