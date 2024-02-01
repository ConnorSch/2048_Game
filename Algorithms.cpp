//
// Created by Connor Schleicher on 2/1/24.
//

#include "Algorithms.h"
#include "RANDOM_MT_H.h"

char Algorithms::next_dir() {
  char dirs[] = "udlr";
  return dirs[Random::get(0,4)];
}
