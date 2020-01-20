//
// Created by matan on 1/16/20.
//

#ifndef HW4_SEARCHALGORITHMS_ISEARCHERSOLVERADAPTER_H_
#define HW4_SEARCHALGORITHMS_ISEARCHERSOLVERADAPTER_H_

#include "interfaces.h"
#include "../searchAlgorithms/interfaces.h"

string solToStringInstructions(vector<State<pair<int,int>>*> solMoves)
{
  bool first = true;
  int prevX;
  int prevY;
  string sol;

  for(auto state : solMoves)
  {
    if(first)
    {
      first = false;
    }
    else
    {
      if(state->getState().first < prevX)
      {
        sol += "up, ";
      }
      else if(state->getState().first > prevX)
      {
        sol += "down, ";
      }
      else if(state->getState().second > prevY)
      {
        sol += "right, ";
      }
      else if(state->getState().second < prevY)
      {
        sol += "left, ";
      }
    }

    prevX = state->getState().first;
    prevY = state->getState().second;
  }

  return sol.substr(0, sol.length()-2);
}

class ISearcherSolverAdopter : public Solver<ISearchable<pair<int, int>>*, string>{
  ISearcher<pair<int, int>>* searcher;
 public:
  explicit ISearcherSolverAdopter(ISearcher<pair<int, int>>* searcher1)
  {
    searcher = searcher1;
  }

  string solve(ISearchable<pair<int, int>>* problem) override
  {
    return solToStringInstructions(searcher->search(problem).getMoves());
  }

  Solver<ISearchable<pair<int, int>>*, string>* clone() override
  {
    return new ISearcherSolverAdopter(searcher->clone());
  }
};

#endif //HW4_SEARCHALGORITHMS_ISEARCHERSOLVERADAPTER_H_
