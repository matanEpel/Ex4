//
// Created by matan on 1/14/20.
//

#ifndef HW4_SEARCHALGORITHMS_SOLUTION_H_
#define HW4_SEARCHALGORITHMS_SOLUTION_H_
#include <vector>
#include "State.h"
#include <algorithm>

template<typename T> class Solution {
  std::vector<State<T>*> moves;
 public:
  void addMove(State<T>* move) {
    Solution::moves.push_back(move);
  }
  double getPrice()
  {
    return (*(moves.end()-1))->getCost();
  }
  std::vector<State<T>*> getMoves() {
    std::reverse(moves.begin(), moves.end());
    return moves;
  }

};

#endif //HW4_SEARCHALGORITHMS_SOLUTION_H_
