//
// Created by matan on 1/14/20.
//

#include "MatrixGraphProblem.h"
#include <limits>
#include <iostream>

double MatrixGraphProblem::getCost(State<pair<int, int>>* curr, State<pair<int, int>>* next) {
  return *(matrixOfCosts + columns*next->getState().first + next->getState().second);
}
vector<State<pair<int, int>>*> MatrixGraphProblem::getAllPossibleStates(State<pair<int, int>>* curr) {
  int row = curr->getState().first;
  int col = curr->getState().second;
  vector<State<pair<int, int>>*> neighbors;
  if(row + 1 < rows  && *(matrixOfCosts+columns*(row + 1) + col) != -1)
  {
    neighbors.push_back((matrixOfStates+columns*(row + 1) + col));
  }
  if(row - 1 >= 0 && *(matrixOfCosts+columns*(row - 1) + col) != -1)
  {
    neighbors.push_back((matrixOfStates+columns*(row - 1) + col));
  }
  if(col + 1 < columns && *(matrixOfCosts+columns*(row) + col + 1) != -1)
  {
    neighbors.push_back((matrixOfStates+columns*(row) + col + 1));
  }
  if(col - 1 >= 0 && *(matrixOfCosts+columns*(row) + col - 1) != -1)
  {
    neighbors.push_back((matrixOfStates+columns*(row) + col - 1));
  }
  if(*(matrixOfCosts+columns*(row) + col)==-1)
  {
    std::cout<<"-1\n";
  }
  return neighbors;
}
bool MatrixGraphProblem::isGoal(State<pair<int, int>>* s) {
  return s->getState().first == finish.first && s->getState().second == finish.second;
}
State<pair<int, int>>* MatrixGraphProblem::getInitialState() {
  return matrixOfStates+columns*(start.first) + start.second;
}
MatrixGraphProblem::MatrixGraphProblem(pair<int, int> start1,
                                       pair<int, int> finish1,
                                       int rows1,
                                       int columns1,
                                       double *matrixOfCosts1) {
  matrixOfCosts = matrixOfCosts1;
  rows = rows1;
  columns = columns1;
  start = start1;
  finish = finish1;

  int size = rows1*columns1;
  matrixOfStates = new State<pair<int, int>>[size];
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < columns; j++)
    {
      State<pair<int, int>> curr(pair<int, int>(i, j), to_string(i) + "-" + to_string(j));
      if(i == 0 && j == 0)
      {
        curr.setCost(*matrixOfCosts);
      }
      else
      {
        curr.setCost(numeric_limits<double>::max());
      }
      curr.setGoalState((matrixOfStates + columns * finish.first + finish.second));
      *(matrixOfStates + columns * i + j) = curr;

    }
  }
}
