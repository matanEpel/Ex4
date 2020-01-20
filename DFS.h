//
// Created by matan on 1/15/20.
//

#ifndef HW4_SEARCHALGORITHMS_DFS_H_
#define HW4_SEARCHALGORITHMS_DFS_H_

#include <unordered_map>
#include <stack>
#include "interfaces.h"


template<typename T> Solution<T> createSolutionFromGoalB(State<T>* goalState, State<T>& start)
{
  Solution<T> sol;
  State<T>* curr = goalState;
  cout<<"price: "<<curr->getCost()<<"\n";
  if(goalState)
  {
    sol.addMove(curr);
    curr = curr->getPrev();
    while(!curr->equals(start))
    {
      sol.addMove(curr);
      curr = curr->getPrev();
    }
    sol.addMove(curr);

    return sol;
  }

  throw "NO GOAL STATE";
}

template<typename T> class DFS : public ISearcher<T>{
  std::stack<State<T>*> stackOfStates;
  unordered_map<string, State<T>*> closedList;
  int numOfNodeExpended = 0;

 public:
  DFS* clone() override
  {
    return new DFS();
  }
  int numberOfNodeExpended()
  {
    return numOfNodeExpended;
  }
  Solution<T> search(ISearchable<T>* problem) {
    auto first = problem->getInitialState();
    stackOfStates.push(first);
    closedList.insert(make_pair(first->getStateString(), first));

    while(stackOfStates.size() != 0)
    {
      State<T>* minState = stackOfStates.top();
      stackOfStates.pop();
      numOfNodeExpended++;

      if(problem->isGoal(minState))
      {
        cout<<"num of nodes: "<<numberOfNodeExpended()<<"\n";
        return createSolutionFromGoalB<T>(minState, *problem->getInitialState());
      }

      vector<State<T>*> neighbors = problem->getAllPossibleStates(minState);
      for(State<T>* curr : neighbors)
      {
        if(closedList.find(curr->getStateString()) == closedList.end())
        {
          curr->setCost(minState->getCost() + problem->getCost(minState, curr));
          curr->setPrev(minState);
          closedList.insert(make_pair(curr->getStateString(), curr));
          stackOfStates.push(curr);
        }
      }
    }
    throw "no solution";
  }
};

#endif //HW4_SEARCHALGORITHMS_DFS_H_
