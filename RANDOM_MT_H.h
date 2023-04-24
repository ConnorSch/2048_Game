//
// Created by Connor Schleicher on 4/24/23.
//

#ifndef INC_2048_PROGRAM_RANDOM_MT_H_H
#define INC_2048_PROGRAM_RANDOM_MT_H_H

#include <chrono>
#include <random>

namespace Random
{
    inline std::mt19937 init()
    {
      std::random_device rd;

      // Create seed_seq with high-res clock and 7 random numbers from std::random_device
      std::seed_seq ss{
              static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()),
              rd(), rd(), rd(), rd(), rd(), rd(), rd() };

      return std::mt19937{ ss };
    }

    // Here's our std::mt19937 PRNG object
    // The inline keyword also means we only have one global instance for our whole program
    inline std::mt19937 mt{ init() };

    // Generate a random number between [min, max] (inclusive)
    inline int get(int min, int max)
    {
      std::uniform_int_distribution die{ min, max };
      return die(mt); // and then generate a random number from our global generator
    }
};


#endif //INC_2048_PROGRAM_RANDOM_MT_H_H
