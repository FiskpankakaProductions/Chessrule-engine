#include <iostream>
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";  // Clear screen and move cursor to top-left
}