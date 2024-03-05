//
// Created by Connor Schleicher on 2/9/24.
//

#include "BST.h"

Node* BST :: insert(Node* root, char direction, int score){
  Node *newNode = new Node(direction, score);
  newNode->left = NULL;
  newNode->right = NULL;
  if(root == NULL){
    root = newNode;
  }
  else if (score >= root->score){
    root->right = insert(root->right, direction, score);
  } else {
    root->left = insert(root->left, direction, score);
  }
  return root;
}

int BST :: search(char searchKey) {
  Node *temp = root;
  while(temp != NULL){
    if(temp->dir == searchKey){
      return searchKey;
    } else if(temp->dir > searchKey){
      temp = temp->left;
    } else {
      temp = temp ->right;
    }
  }
  return -1;
}


void BST :: preOrder(Node* root){
  if(root != NULL){
    std::cout << root->dir << " ";
    preOrder(root->left);
    preOrder(root->right);
  }
}

void BST :: inOrder(Node* root) {
  if(root != NULL){
    inOrder(root->left);
    std::cout << root-> dir << " ";
    inOrder(root->right);
  }
}


void BST :: postOrder(Node* root) {
  //Write your code here
  if(root != NULL){
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root-> dir << " ";
  }
}

char BST::maxNode(Node* root) {
  char t_dir;
  if (root->right == NULL)
    t_dir = root->dir;
  else {
    t_dir = maxNode(root->right);
  }
  return t_dir;
}
