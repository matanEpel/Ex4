//
// Created by matan on 1/15/20.
//


//
// Created by matan on 1/15/20.
//

#ifndef HW4_SEARCHALGORITHMS_ASTAR_H_
#define HW4_SEARCHALGORITHMS_ASTAR_H_

#include <queue>
#include <unordered_map>
#include "State.h"
#include "interfaces.h"

template<typename T> Solution<T> createSolutionFromGoalA(State<T>* goalState, State<T>& start)
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

template <typename T> struct LessThanByPriceAndH
{
  bool operator()(State<T>*& first, State<T>*& second) const
  {
    double firstH = first->heuristicDistance();
    double secondH = second->heuristicDistance();
    return first->getCost() + firstH > second->getCost() + secondH;
  }
};


template<typename T> class AStar : public ISearcher<T>{
  std::priority_queue<State<T>*, vector<State<T>*>, LessThanByPriceAndH<T>> queue;
  unordered_map<string, State<T>*> closedList;
  int numOfNodeExpended = 0;
  //queue.push(State);

 public:
  ISearcher<T>* clone()
  {
    return new AStar();
  }

  int numberOfNodeExpended()
  {
    return numOfNodeExpended;
  }
  Solution<T> search(ISearchable<T>* problem) {
    auto first = problem->getInitialState();
    queue.push(first);
    closedList.insert(make_pair(first->getStateString(), first));

    while(queue.size() != 0)
    {
      State<T>* minState = queue.top();
      queue.pop();
      numOfNodeExpended++;

      if(problem->isGoal(minState))
      {
        cout<<"num of nodes: "<<numberOfNodeExpended()<<"\n";
        return createSolutionFromGoalA<T>(minState, *problem->getInitialState());
      }

      vector<State<T>*> neighbors = problem->getAllPossibleStates(minState);
      for(State<T>* curr : neighbors)
      {
        if(minState->getCost() + problem->getCost(minState, curr) < curr->getCost())
        {
          curr->setCost(minState->getCost() + problem->getCost(minState, curr));
          if(closedList.find(curr->getStateString()) == closedList.end())
          {
            curr->setPrev(minState);
            closedList.insert(make_pair(curr->getStateString(), curr));
            queue.push(curr);
          }
          else
          {
            curr->setPrev(minState);
            vector<State<T>*> copy;
            while(queue.size() != 0)
            {
              copy.push_back(queue.top());
              queue.pop();
            }
            while(copy.size() != 0)
            {
              queue.push(copy.back());
              copy.pop_back();
            }
          }
        }
      }
    }

  }
};

#endif //HW4_SEARCHALGORITHMS_PRIORITYBASEDALGS_H_
