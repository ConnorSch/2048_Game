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
    Board(size_t M, size_t N) : num_rows_(M), num_cols_(N), storage_(num_rows_ * num_cols_) {
      storage_[Random::get(0,M) * Random::get(0, N) + N] = 2;
    }

    double&       operator()(size_t i, size_t j) { return storage_[i * num_cols_ + j]; }
    const double& operator()(size_t i, size_t j) const { return storage_[i * num_cols_ + j]; }


    size_t num_rows() const { return num_rows_; }
    size_t num_cols() const { return num_cols_; }

    friend std::ostream& operator<< (std::ostream& out, const Board& board);

private:
    size_t              num_rows_, num_cols_;
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

#endif //UNTITLED3_BOARD_H
