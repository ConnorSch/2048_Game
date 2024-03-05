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
       game_score_ = 0;
       invalid_move_ = false;
    }

    int&       operator()(int i, int j) { return storage_[i * num_cols_ + j]; }
    const int& operator()(int i, int j) const { return storage_[i * num_cols_ + j]; }

    int move(Board &board, char dir);
    static std::pair<std::vector<int>,bool> movement(Board &board, std::vector<int> row,bool reverse_row);

    [[nodiscard]] int num_rows() const { return num_rows_; }
    [[nodiscard]] int num_cols() const { return num_cols_; }
    [[nodiscard]] std::vector<int> storage() const {return storage_;}
    [[nodiscard]] int num_moves() const {return num_moves_;}
    [[nodiscard]] int game_score() const {return game_score_;}
    [[nodiscard]] bool game_over() const {return game_over_;}
    [[nodiscard]] bool invalid_move() const {return invalid_move_;}

    friend std::ostream& operator<< (std::ostream& out, const Board& board);

    void random_position(){
      // the next row is used for debugging purposes to always put the random digit in the first cell
      //storage_[0] = 2;
      auto pos = Random::get(0,num_rows_ - 1) * Random::get(0, num_cols_ - 1) + num_cols_;
      auto two_four = Random::get(0,10);
      int assignment = 2;
      if(two_four > 7){assignment = 4;}
      storage_[pos] = assignment;
    }

    bool next_added_digit(){
      std::vector<int> zeros_index;
      for (int i = 0; i < storage_.size(); ++i) {
        if (storage_[i] == 0){
          zeros_index.push_back(i);
        }
      }
      if (zeros_index.empty()){
        game_over_ = true;
        //std::cout << "Game over!" << std::endl;
        //std::cout << "Thanks for playing, your number of moves is: " << num_moves_ << std::endl;
        return true;
      } else {
        int next_num_position = Random::get(0, zeros_index.size()-1);
        storage_[zeros_index[next_num_position]] = 2;
        return false;
      }
      // the next row is used for debugging purposes to always put the random digit in the first cell
      //storage_[0] = 2;
    }

private:
    int              num_rows_, num_cols_;
    std::vector<int> storage_;
    bool game_over_;
    int num_moves_;
    int game_score_;
    int invalid_move_;
};

#endif //UNTITLED3_BOARD_H
