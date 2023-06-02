#include <iostream>

#include "Board.h"

int main() {
  Board Game_Board(4,4);
  std::cout << Game_Board;

  bool keep_playing = true;
  while (keep_playing) {
    std::cout << "Enter a movement direction (l/r/u/d)(n to stop playing): " << std::endl;
    char dir;
    std::cin >> dir;
    if(dir == 'n'){
      keep_playing = false;
    } else {
      Game_Board = Game_Board.move(Game_Board, dir);
      std::cout << Game_Board;
    }
  }
  return 0;
}
