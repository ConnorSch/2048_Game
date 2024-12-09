//
// Created by Connor Schleicher on 2/1/24.
//

#include "Algorithms.h"
#include "RANDOM_MT_H.h"
#include <queue>

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
  Board new_board(board);
  Node* root = new Node(new_board);
  std::queue<std::pair<Node*, int>> q;
  q.emplace(root, 0);
  int targetDepth = 2;

  while(!q.empty()){
    Node* currentNode = q.front().first;
    int currentDepth = q.front().second;
    q.pop();

    for (int i = 0; i < 4; ++i) {
      auto child_root = currentNode;
      Board move_board(child_root->_node_board);
      move_board.move(move_board, dirs[i]);
      if (!move_board.game_over() or !move_board.invalid_move()){
        currentNode->children.push_back(new Node(move_board, child_root));
      }
    }
    if (currentDepth == targetDepth) continue;
    for (Node* child : currentNode->children){
        q.emplace(child, currentDepth + 1);
    }
  }

  auto maxScorePath = root->findMaxPath();


  return maxScorePath[0].second;
}