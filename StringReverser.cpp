//
// Created by matan on 1/14/20.
//

#include "StringReverser.h"
string StringReverser::solve(string problem) {
  reverse(problem.begin(), problem.end());
  return problem;
}
