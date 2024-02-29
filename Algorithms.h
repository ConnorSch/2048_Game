//
// Created by Connor Schleicher on 2/1/24.
//

#ifndef INC_2048_PROGRAM_ALGORITHMS_H
#define INC_2048_PROGRAM_ALGORITHMS_H

#include <iostream>
#include <utility>
#include "Board.h"
#include "BST.h"

class Algorithms {
public:

  Algorithms(std::string type): type_(type){}

  char next_dir(Algorithms &alg,Board &Board);
  void set_last_move(char dir) {last_move_ = dir;}
  char eval(Board &Board);

private:
    std::string type_;
    char last_move_;

};


#endif //INC_2048_PROGRAM_ALGORITHMS_H
