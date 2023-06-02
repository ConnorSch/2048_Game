//
// Created by Connor Schleicher on 4/24/23.
//

#ifndef UNTITLED3_BOARD_H
#define UNTITLED3_BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "RANDOM_MT_H.h"

class Board {
public:
    Board(int M, int N, bool RandStart = true) : num_rows_(M), num_cols_(N), storage_(num_rows_ * num_cols_) {
       if(RandStart){random_position();}
       game_over_ = false;
       num_moves_ = 0;
    }

    int&       operator()(int i, int j) { return storage_[i * num_cols_ + j]; }
    const int& operator()(int i, int j) const { return storage_[i * num_cols_ + j]; }

    Board move(Board &board, char dir);
    std::pair<std::vector<int>,bool> movement(std::vector<int> row,bool reverse_row);

    [[nodiscard]] int num_rows() const { return num_rows_; }
    [[nodiscard]] int num_cols() const { return num_cols_; }

    friend std::ostream& operator<< (std::ostream& out, const Board& board);

    void random_position(){
      // the next row is used for debugging purposes to always put the random digit in the first cell
      //storage_[0] = 2;
      storage_[Random::get(0,num_rows_ - 1) * Random::get(0, num_cols_ - 1) + num_cols_] = 2;
    }

    void next_added_digit(){
      if (game_over_){
        std::cout << "Game over!" << std::endl;
        std::cout << "Thanks for playing, your number of moves is: " << num_moves_ << std::endl;
      } else {
        std::vector<int> zeros_index;
        for (int i = 0; i < storage_.size(); ++i) {
          if (storage_[i] == 0){
            zeros_index.push_back(i);
          }
        }
        int next_num_position = Random::get(0, zeros_index.size());
        // the next row is used for debugging purposes to always put the random digit in the first cell
        //storage_[0] = 2;
        storage_[zeros_index[next_num_position]] = 2;
      }
    }

private:
    int              num_rows_, num_cols_;
    std::vector<int> storage_;
    bool game_over_;
    int num_moves_;
};

std::ostream& operator<< (std::ostream &out, const Board &board)
{
  std::cout << "Current Board Values: " << std::endl;
  for (int i = 0; i < board.num_rows_; ++i) {
    for (int j = 0; j < board.num_cols_; ++j) {
      out << board(i, j) << " ";
    }  std::cout << std::endl;
  }
  return out;
}

Board Board::move(Board &board, char dir){
  int num_cols = board.num_cols();
  int num_rows = board.num_rows();
  board.num_moves_++;
  std::vector<int> row;
  std::pair<std::vector<int>,bool> move_response;
  bool move_able[4] = {false};

  switch (dir){
    case 'd':
      for (int j = 0; j < num_cols; ++j) {
        for (int i = 0; i < num_rows; ++i) {
          row.push_back(board(i,j));
        }
        move_response = movement(row, true);
        std::vector<int> response_row = move_response.first;
        move_able[j] = move_response.second;
        for (int k = 0; k < response_row.size(); ++k) {
          board(k,j) = response_row[k];
        }
        response_row.clear();
        row.clear();
      }
      break;
    case 'r':
      for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
          row.push_back(board(i,j));
        }
        move_response = movement(row, true);
        std::vector<int> response_row = move_response.first;
        move_able[i] = move_response.second;

        for (int k = 0; k < response_row.size(); ++k) {
          board(i,k) = response_row[k];
        }
        response_row.clear();
        row.clear();
      }
      break;
    case 'l':
      for (int i = 0; i < num_rows; ++i) {
        for (int j = num_cols - 1; j >= 0; --j) {
          row.push_back(board(i,j));
        }
        move_response = movement(row, false);
        std::vector<int> response_row = move_response.first;
        move_able[i] = move_response.second;
        for (int k = 0; k < response_row.size(); ++k) {
          board(i,k) = response_row[k];
        }
        response_row.clear();
        row.clear();
      }
      break;
    case 'u':
      for (int j = 0; j < num_cols; ++j) {
        for (int i = num_rows - 1; i >= 0; --i) {
          row.push_back(board(i,j));
        }
        move_response = movement(row, false);
        std::vector<int> response_row = move_response.first;
        move_able[j] = move_response.second;
        for (int k = 0; k < response_row.size(); ++k) {
          board(k, j) = response_row[k];
        }
        response_row.clear();
        row.clear();
      }
      break;
  }
  //if all of move_able is true then can't make that move
  board.next_added_digit();
  return board;
}

std::pair<std::vector<int>,bool> Board::movement(std::vector<int> row, bool reverse_row){
  int n = row.size();
  bool invalid_move = false;
  std::vector<int> return_vec;
  /* reverse through the row and double the numbers where necessary
   want to reverse through since you don't want cascading numbers to combine for example:
   [2 0 2 4] should become [0 0 4 4] not [0 0 0 8]
  */
  for (int i = n-1; i >= 0; --i) {
    if (row[i] != 0){
      if (!return_vec.empty() && return_vec.back() == row[i]){
        return_vec.back() = row[i] * 2;
      } else {
        return_vec.push_back(row[i]);
      }
    }
  }

  // add in any 0s to fluff the return vector back to n number of rows
  int filler = n - return_vec.size();
  for (int i = 0; i < filler; ++i) {
    return_vec.push_back(0);
  }

  std::vector<int> rev_return_vec(n);
  if (reverse_row){
    std::reverse_copy(std::begin(return_vec), std::end(return_vec), std::begin(rev_return_vec));
  } else {
    rev_return_vec = return_vec;
  }


  if (row == rev_return_vec && filler == 0){
    invalid_move = true;
  }
  return std::make_pair(rev_return_vec,invalid_move);
}


#endif //UNTITLED3_BOARD_H
