//
// Created by Connor Schleicher on 2/1/24.
//

#include "Algorithms.h"
#include "RANDOM_MT_H.h"

char Algorithms::next_dir(Algorithms &alg, Board &Board) {
  char dir;
  if(alg.type_ == "random"){
    int seed = Random::get(0,3);
    switch (seed) {
      case 0:
        dir = 'u';
      case 1:
        dir = 'd';
      case 2:
        dir = 'l';
      case 3:
        dir = 'r';
      default:
        dir = 'd';
    }
    alg.last_move_ = dir;
  } else if(alg.type_ == "corner"){
    if (alg.last_move_ == 'l'){
      alg.set_last_move('d');
      dir = 'd';
    } else{
      alg.set_last_move('l');
      dir = 'l';
    }
  } else if (alg.type_ == "eval"){
    dir = eval(Board);
  } else {
    dir = 'd';
  }


  return dir;
}

char Algorithms::eval(Board &board){
  char dirs[4]  {'u','d','l','r'};
  BST tree;
  tree.root = tree.insert(tree.root, 'a', board.game_score());
  for (int i = 0; i < 4; ++i) {
    Board new_board = board;
    new_board.move(new_board, dirs[i]);
    int eval_score = new_board.game_score();
    if(new_board.game_over()) {
      eval_score = -1;
    } else if(new_board.invalid_move()){
      eval_score = 0;
    }
    tree.root = tree.insert(tree.root, dirs[i], eval_score);
  }
  char ret = tree.maxNode(tree.root);
  return ret;
}