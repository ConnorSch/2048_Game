//
// Created by Connor Schleicher on 2/9/24.
//

#ifndef INC_2048_PROGRAM_BST_H
#define INC_2048_PROGRAM_BST_H

#include <iostream>
#include <utility>
#include "Board.h"

class Node
{
public:
    Board _node_board;
    Node* _parent;
    std::vector<Node*> children;

    explicit Node(Board game, Node* parent = nullptr) : _node_board(std::move(game)), _parent(parent){}

    std::vector<std::pair<int,char>> findMaxPath();
};

#endif //INC_2048_PROGRAM_BST_H
