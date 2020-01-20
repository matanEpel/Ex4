//
// Created by matan on 1/14/20.
//

#ifndef HW4_SEARCHALGORITHMS_INTERFACES_H_
#define HW4_SEARCHALGORITHMS_INTERFACES_H_

#include "Solution.h"
#include "State.h"

template <typename T> class ISearchable {
 public:
  virtual State<T>* getInitialState() = 0;
  virtual bool isGoal(State<T>* s) = 0;
  virtual vector<State<T>*> getAllPossibleStates(State<T>* curr) = 0;
  virtual double getCost(State<T>* curr, State<T>* next) = 0;
};

template <typename T> class ISearcher {
 public:
  virtual Solution<T> search(ISearchable<T>* problem) = 0;
  virtual ISearcher<T>* clone() = 0;
  virtual int numberOfNodeExpended() = 0;
};
#endif //HW4_SEARCHALGORITHMS_INTERFACES_H_
