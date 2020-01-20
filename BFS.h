//
// Created by matan on 1/15/20.
//

#ifndef HW4_SEARCHALGORITHMS_BFS_H_
#define HW4_SEARCHALGORITHMS_BFS_H_

#include <unordered_map>
#include <stack>
#include <queue>
#include "interfaces.h"

template<typename T> Solution<T> createSolutionFromGoalC(State<T>* goalState, State<T>& start)
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

template<typename T> class BFS : public ISearcher<T>{
  std::queue<State<T>*> queueOfStates;
  unordered_map<string, State<T>*> closedList;
  int numOfNodeExpended = 0;

 public:
  BFS* clone() override
  {
    return new BFS();
  }
  int numberOfNodeExpended()
  {
    return numOfNodeExpended;
  }
  Solution<T> search(ISearchable<T>* problem) {
    auto first = problem->getInitialState();
    queueOfStates.push(first);
    closedList.insert(make_pair(first->getStateString(), first));

    while(queueOfStates.size() != 0)
    {
      State<T>* minState = queueOfStates.front();
      queueOfStates.pop();
      numOfNodeExpended++;

      if(problem->isGoal(minState))
      {
        cout<<"num of nodes: "<<numberOfNodeExpended()<<"\n";
        return createSolutionFromGoalC<T>(minState, *problem->getInitialState());
      }

      vector<State<T>*> neighbors = problem->getAllPossibleStates(minState);
      for(State<T>* curr : neighbors)
      {
        if(closedList.find(curr->getStateString()) == closedList.end())
        {
          curr->setCost(minState->getCost() + problem->getCost(minState, curr));
          curr->setPrev(minState);
          closedList.insert(make_pair(curr->getStateString(), curr));
          queueOfStates.push(curr);
        }
      }
    }
    throw "no solution";
  }
};

#endif //HW4_SEARCHALGORITHMS_BFS_H_
