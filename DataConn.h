//
// Created by Connor Schleicher on 7/17/23.
//

#ifndef INC_2048_PROGRAM_DATACONN_H
#define INC_2048_PROGRAM_DATACONN_H

#include <sqlite3.h>
#include <string>
#include <utility>

class DataConn {
public:
    DataConn(const char* db_name) : db_name_(db_name){
      sqlite3* DB;
      exit_ = sqlite3_open(db_name, &DB);
    }

    static int callback(void* data, int argc, char** argv, char** azColName);



private:
    const char* db_name_;
    sqlite3* DB_;
    int exit_;
};


#endif //INC_2048_PROGRAM_DATACONN_H
