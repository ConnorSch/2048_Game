//
// Created by Connor Schleicher on 2/9/24.
//

#include "BST.h"


std::vector<std::pair<int, char>> Node::findMaxPath() {
  std::vector<std::pair<int, char>> maxPath;
  std::vector<std::pair<int,char>> currentPath;

  int maxValue = std::numeric_limits<int>::min();

  std::function<void(Node*)> traverse = [&](Node* node){
    if (!node) return;

    int game_score = node->_node_board.game_score();
    char game_dir = node->_node_board.last_move();
    currentPath.emplace_back(game_score, game_dir);
    if (game_score > maxValue){
      maxValue = game_score;
      maxPath = currentPath;
    }
    for (Node* child : node->children){
      traverse(child);
    }
    currentPath.pop_back();
  };
  traverse(this);
  return maxPath;
}
