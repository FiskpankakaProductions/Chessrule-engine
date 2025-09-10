#include "data.h"

#include <iostream>
#include <string>

bool isLegal (int pice, std::string move) {
	if (pice % 2 == 0) {
		if (pice == 2) {
			return true;
		}
		else if (pice == 4) {
			return true;
		}
		else if (pice == 6) {
			return true;
		}
		else if (pice == 8) {
			return true;
		}
		else if (pice == 10) {
			return true;
		}
		else if (pice == 12) {
			return true;
		}
	}
	else {
		if (pice == 3) {
			return true;
		}
		else if (pice == 5) {
			return true;
		}
		else if (pice == 7) {
			return true;
		}
		else if (pice == 9) {
			return true;
		}
		else if (pice == 11) {
			return true;
		}
		else if (pice == 13) {
			return true;
		}
	}	
return false;
}
