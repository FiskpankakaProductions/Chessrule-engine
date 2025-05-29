#include <iostream>
using namespace std;

int action;

void start() {

}

void settings(){
  cout << "[1]: GUI\n[2]: Logic\n[0]: Exit";
  cin >> action;
  if (action == 1) {

  } else if (action == 2) {

  } else if (action == 0) {

  } else {
    cout << "Unkown Command";
  }
}

int main() {
  cout << "Menu\n";
  cout << "[1]: Start\n[2]: Settings\n[0]: Exit\n";
  cin >> action;
  if (action == 1) {
    start();
  } else if (action == 2) {
    settings();
  } else if (action == 0) {
    
  } else {
    cout << "Unkown Command";
  }

  return 0;
}