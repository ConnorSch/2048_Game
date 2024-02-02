#include <iostream>
#include "Board.h"
#include "Algorithms.h"
#include "DataConn.h"
#include <sqlite3.h>
#include <string>

static int callback(void* data, int argc, char** argv, char** azColName)
{
  int i;
  fprintf(stderr, "%s: ", (const char*)data);

  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
  return 0;
}

void create_table(sqlite3* DB, const char* db_name)
{
  std::string sql = "create table if not exists GAME_BOARD("
                    "GAME_ID        INT     NOT NULL, "
                    "TURN_NUM       INT     NOT NULL, "
                    "MOVE           TEXT    NULL, "
                    "POS_0          INT     NOT NULL,"
                    "POS_1          INT     NOT NULL,"
                    "POS_2          INT     NOT NULL,"
                    "POS_3          INT     NOT NULL,"
                    "POS_4          INT     NOT NULL,"
                    "POS_5          INT     NOT NULL,"
                    "POS_6          INT     NOT NULL,"
                    "POS_7          INT     NOT NULL,"
                    "POS_8          INT     NOT NULL,"
                    "POS_9          INT     NOT NULL,"
                    "POS_10         INT     NOT NULL,"
                    "POS_11         INT     NOT NULL,"
                    "POS_12         INT     NOT NULL,"
                    "POS_13         INT     NOT NULL,"
                    "POS_14         INT     NOT NULL,"
                    "POS_15         INT     NOT NULL);";
  int exit = 0;
  exit = sqlite3_open(db_name, &DB);
  char* messageError;
  exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
  int return_value;
  if (exit != SQLITE_OK) {
    std::cerr << "Error Create Table " << std::endl;
    sqlite3_free(messageError);
    return_value = 1;
  }
  else {
    std::cout << "Table created successfully!" << std::endl;
    return_value = 0;
  }
  sqlite3_close(DB);
  //return return_value;
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

template<typename Function>
void store_state(Board &board, sqlite3* DB, const char* db_name, Function callback, int id, char dir){
  char* messageError;
  int exit = sqlite3_open(db_name, &DB);
  std::vector<int> other_adds = {1, board.num_rows(), 0};
  std::string vector_str = values_to_string(board.storage());

  std::string str_dir;
  str_dir += dir;
  std::string insert_str = "(" + std::to_string(id) + "," + std::to_string(board.num_moves()) + ",'" + str_dir + "',";
  insert_str += vector_str + ")";

  std::string query = "INSERT INTO GAME_BOARD (GAME_ID,TURN_NUM,MOVE,POS_0,POS_1,POS_2,POS_3,POS_4,POS_5,POS_6,POS_7,POS_8,POS_9,POS_10,POS_11,POS_12,POS_13,POS_14,POS_15) VALUES " + insert_str;
  exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messageError);
  if (exit != SQLITE_OK) {
    std::cerr << "Error Insert" << std::endl;
    sqlite3_free(messageError);
  }
  else
    std::cout << "Records created Successfully!" << std::endl;
  sqlite3_close(DB);
}


void automatic_play(int game_id, std::pair<const char*, sqlite3*> db_info){
  int keep_playing = 1;
  Board Game_Board(4,4);
  Algorithms Alg("random");
  while(keep_playing != 0){
    char dir = Alg.next_dir(Alg);
    keep_playing = Game_Board.move(Game_Board, dir);
    if(keep_playing != -1){
      store_state(Game_Board, db_info.second, db_info.first, callback, game_id, dir);
    }
  }
}


int main() {
 //create the sqlite database
  const char *db_name = "boardStates.db";
  DataConn Conn(db_name);
  sqlite3* DB;
  int exit = 0;
  exit = sqlite3_open(db_name, &DB);

  if (exit) {
    std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
    return (-1);
  }
  else {
    std::cout << "Opened Database Successfully!" << std::endl;
  }
  create_table(DB, db_name);

  int t = sqlite3_open(db_name, &DB);
  char* messageError;
  std::string query = "SELECT MAX(GAME_ID) FROM GAME_BOARD";
  //std::string query = "SELECT DISTINCT GAME_ID FROM GAME_BOARD";

  int gameID = 0;
  sqlite3_stmt *stmt;
  const char *sql = "SELECT MAX(GAME_ID) FROM GAME_BOARD";
  int rc = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    std::cerr << "Error:" << sqlite3_errmsg(DB) << std::endl;
  }
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    gameID = sqlite3_column_int (stmt, 0);
    const unsigned char *name = sqlite3_column_text(stmt, 1);
    // ...
  }
  if (rc != SQLITE_DONE) {
    std::cerr << "Error:" << sqlite3_errmsg(DB) << std::endl;
  }
  sqlite3_finalize(stmt);
  gameID++;

  bool auto_play = true;
  if(!auto_play){
    Board Game_Board(4,4);
    std::cout << Game_Board;

    int keep_playing = 1;
    while (keep_playing != 0) {
      std::cout << "Enter a movement direction (l/r/u/d)(n to stop playing): " << std::endl;
      char dir;
      std::cin >> dir;
      if(dir == 'n'){
        keep_playing = 0;
      } else {
        keep_playing = Game_Board.move(Game_Board, dir);
        store_state(Game_Board, DB, db_name, callback, gameID, dir);
        std::cout << Game_Board;
      }
    }
  } else {
    automatic_play(gameID, std::make_pair(db_name,DB));
  }



  sqlite3_close(DB);

  return 0;
}
