//
// Created by Connor Schleicher on 2/1/24.
//

#ifndef INC_2048_PROGRAM_ALGORITHMS_H
#define INC_2048_PROGRAM_ALGORITHMS_H

#include <iostream>
#include <utility>

class Algorithms {
public:
  Algorithms(std::string type): type_(type){}

  char next_dir(Algorithms &alg);


private:
    std::string type_;

};


#endif //INC_2048_PROGRAM_ALGORITHMS_H
