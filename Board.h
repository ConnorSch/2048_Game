//
// Created by Connor Schleicher on 4/24/23.
//

#ifndef UNTITLED3_BOARD_H
#define UNTITLED3_BOARD_H

#include <iostream>
#include <vector>
#include "RANDOM_MT_H.h"

class Board {
public:
    Board(int M, int N, bool RandStart = false) : num_rows_(M), num_cols_(N), storage_(num_rows_ * num_cols_) {
       if(RandStart){random_position();}
    }

    double&       operator()(int i, int j) { return storage_[i * num_cols_ + j]; }
    const double& operator()(int i, int j) const { return storage_[i * num_cols_ + j]; }

    Board move(Board &board, char dir);

    [[nodiscard]] int num_rows() const { return num_rows_; }
    [[nodiscard]] int num_cols() const { return num_cols_; }

    friend std::ostream& operator<< (std::ostream& out, const Board& board);

    void random_position(){
      storage_[Random::get(0,num_rows_ - 1) * Random::get(0, num_cols_ - 1) + num_cols_] = 2;
    }

private:
    int              num_rows_, num_cols_;
    std::vector<double> storage_;
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

Board Board::move(Board &board, char dir) {
  Board new_board = Board(board.num_rows_, board.num_cols_);

  for (int i = 0; i < board.num_rows(); ++i) {
    for (int j = 0; j < board.num_cols(); ++j) {
      switch (dir) {
        case 'd':
          if ((i + 1) < board.num_rows()){
            if ((board(i, j) == board(i + 1, j)) && board(i,j) != 0) {
              new_board(i + 1, j) = 2 * board(i, j);
            } else if (board(i,j) != 0 && board(i + 1, j) == 0){
              new_board(i + 1, j) = board(i, j);
            }
          } else if ((i + 1) == board.num_rows()){
            if (new_board(i,j) == 0) {
              new_board(i, j) = board(i, j);
            }
          }
          break;
        case 'u':
          if ((i - 1) >= 0){
            if ((board(i, j) == board(i - 1, j)) && board(i,j) != 0) {
              new_board(i - 1, j) = 2 * board(i, j);
            } else if (board(i,j) != 0 && board(i - 1, j) == 0){
              new_board(i - 1, j) = board(i, j);
            }
          } else if ((i - 1) < 0){
            if (new_board(i,j) == 0) {
              new_board(i, j) = board(i, j);
            }
          }
          break;
        case 'l':
          if ((j - 1) >= 0){
            if ((board(i, j) == board(i, j - 1)) && board(i,j) != 0) {
              new_board(i, j - 1) = 2 * board(i, j);
            } else if (board(i,j) != 0 && board(i, j - 1) == 0){
              new_board(i, j - 1) = board(i, j);
            }
          } else if ((j - 1) < 0){
            if (new_board(i,j) == 0) {
              new_board(i, j) = board(i, j);
            }
          }
          break;
        case 'r':
          if ((j + 1) < board.num_cols()){
            if ((board(i, j) == board(i, j + 1)) && board(i,j) != 0) {
              new_board(i, j + 1) = 2 * board(i, j);
            } else if (board(i,j) != 0 && board(i, j + 1) == 0){
              new_board(i, j + 1) = board(i, j);
            }
          } else if ((j + 1) == board.num_cols()){
            if (new_board(i,j) == 0) {
              new_board(i, j) = board(i, j);
            }
          }
          break;
      }
    }
  }

  return new_board;
}

#endif //UNTITLED3_BOARD_H
