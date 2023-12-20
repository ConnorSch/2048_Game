//
// Created by Connor Schleicher on 7/17/23.
//

#include "DataConn.h"

int DataConn::callback(void* data, int argc, char** argv, char** azColName)
{
  int i;
  fprintf(stderr, "%s: ", (const char*)data);

  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
  return 0;
}