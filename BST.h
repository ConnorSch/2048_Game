//
// Created by Connor Schleicher on 2/9/24.
//

#ifndef INC_2048_PROGRAM_BST_H
#define INC_2048_PROGRAM_BST_H

#include <iostream>
#include "Board.h"

class Node
{
public:
    Node(){};
    Node(Board &board){
      Board node_board_ = board;
    };

    Node *left, *right;
private:
    Board node_board_;
};

class BST
{
public :
    Node *root;
    BST() {
      root = NULL;
    }
    Node* insert(Node*, char, int);
    int search(char);
    void preOrder(Node*);
    void inOrder(Node*);
    void postOrder(Node*);
    char maxNode(Node*);
};



#endif //INC_2048_PROGRAM_BST_H
