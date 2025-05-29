#include <iostream>
using namespace std;

int action;

bool running = true;

void start() {

}

void settings(){
  
}

int main() {
  while (running)
  {
    cout << "Menu\n";
    cout << "[1]: Start\n[2]: Settings\n[0]: Exit\n";
    cin >> action;
    if (action == 1) {
      start();
    } else if (action == 2) {
      settings();
    } else if (action == 0) {
      running = false;
    } else {
      cout << "Unkown Command";
    }
  }
  return 0;
}