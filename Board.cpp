//
// Created by Connor Schleicher on 4/24/23.
//

#include "Board.h"

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

std::string values_to_string(std::vector<int> values){
  std::string val_str;
  for(int i = 0; i < size(values); ++i){
    val_str += std::to_string(values[i]);
    if (i < (size(values)-1)){
      val_str += ",";
    }
  }
  return val_str;
}

bool Board::move(Board &board, char dir){
  int num_cols = board.num_cols();
  int num_rows = board.num_rows();
  board.num_moves_++;
  std::vector<int> row;
  std::pair<std::vector<int>,bool> move_response;
  bool invalid_moves[4] = {false};

  switch (dir){
    case 'd':
      for (int j = 0; j < num_cols; ++j) {
        for (int i = 0; i < num_rows; ++i) {
          row.push_back(board(i,j));
        }
        move_response = movement(row, true);
        std::vector<int> response_row = move_response.first;
        invalid_moves[j] = move_response.second;
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
        invalid_moves[i] = move_response.second;

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
        invalid_moves[i] = move_response.second;
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
        invalid_moves[j] = move_response.second;
        for (int k = 0; k < response_row.size(); ++k) {
          board(k, j) = response_row[k];
        }
        response_row.clear();
        row.clear();
      }
      break;
    default:
      std::cout << "Invalid move, please enter a valid move direction" <<std::endl;
  }
  //if all of invalid_moves is true then can't make that move

  bool end_game = false;
  int sum = std::accumulate(invalid_moves, invalid_moves + 4, 0);
  if (sum == 4){
    std::cout<< "try a different direction, combinations found" << std::endl;
  } else {
    end_game = board.next_added_digit();
  }
  if (end_game){
    return false;
  } else {
    return true;
  }


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

template<typename Function>
void Board::store_state(Board &board, sqlite3* DB, const char* db_name, Function callback){
  char* messageError;
  int exit = sqlite3_open(db_name, &DB);
  std::vector<int> other_adds = {1, board.num_rows(), 0};
  std::string vector_str = values_to_string(board.storage());
  std::string insert_str = "(1," + std::to_string(board.num_rows()) + ",NULL";
  insert_str += vector_str + ")";

  std::string query = "INSERT INTO GAME_BOARD VALUES " + insert_str;
  exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messageError);
  if (exit != SQLITE_OK) {
    std::cerr << "Error Insert" << std::endl;
    sqlite3_free(messageError);
  }
  else
    std::cout << "Records created Successfully!" << std::endl;
  sqlite3_close(DB);
}


