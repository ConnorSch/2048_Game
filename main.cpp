#include <iostream>
#include "Board.h"
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

int main() {
 //create the sqlite database
  sqlite3* DB;
  const char *db_name = "boardStates.db";
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


  Board Game_Board(4,4);
  std::cout << Game_Board;

  bool keep_playing = true;
  while (keep_playing) {
    std::cout << "Enter a movement direction (l/r/u/d)(n to stop playing): " << std::endl;
    char dir;
    std::cin >> dir;
    if(dir == 'n'){
      keep_playing = false;
    } else {
      keep_playing = Game_Board.move(Game_Board, dir);
      Game_Board.store_state(Game_Board, DB, db_name, callback);
      std::cout << Game_Board;
    }
  }

  sqlite3_close(DB);

  return 0;
}
