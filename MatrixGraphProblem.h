//
// Created by matan on 1/14/20.
//

#ifndef HW4_SEARCHALGORITHMS_MATRIXGRAPHPROBLEM_H_
#define HW4_SEARCHALGORITHMS_MATRIXGRAPHPROBLEM_H_

#include "interfaces.h"
class MatrixGraphProblem : public ISearchable<pair<int, int>>{
  double* matrixOfCosts;
  State<pair<int, int>>* matrixOfStates;
  int rows = 0;
  int columns = 0;
  pair<int, int> start;
  pair<int, int> finish;
 public:
  MatrixGraphProblem(pair<int, int> start1, pair<int, int> finish1, int rows1, int columns1, double* matrixOfCosts1);
  State<pair<int, int>>* getInitialState() override;
  bool isGoal(State<pair<int, int>>* s) override;
  vector<State<pair<int, int>>*> getAllPossibleStates(State<pair<int, int>>* curr) override;
  double getCost(State<pair<int, int>>* curr, State<pair<int, int>>* next) override;
};

#endif //HW4_SEARCHALGORITHMS_MATRIXGRAPHPROBLEM_H_
