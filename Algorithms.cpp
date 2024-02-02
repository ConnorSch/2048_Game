//
// Created by Connor Schleicher on 2/1/24.
//

#include "Algorithms.h"
#include "RANDOM_MT_H.h"

char Algorithms::next_dir(Algorithms &alg) {
  if(alg.type_ == "random"){
    int seed = Random::get(0,3);
    switch (seed) {
      case 0:
        return 'u';
      case 1:
        return 'd';
      case 2:
        return 'l';
      case 3:
        return 'r';
      default:
        return 'd';
    }
  } else if(alg.type_ == "corner"){
    return 'd';
  } else {
    return 'd';
  }
}
