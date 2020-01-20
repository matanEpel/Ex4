//
// Created by matan on 1/14/20.
//

#ifndef HW4_SEARCHALGORITHMS_STATE_H_
#define HW4_SEARCHALGORITHMS_STATE_H_

#include <string>
#include <type_traits>

using namespace std;
template<typename T> class State {
  State<T>* prevState;
  State<T>* goalState;
  double costToState;
  T state;
  string stateRepresentation;

 public:
  double heuristicDistance()
  {
    if(std::is_same<T, pair<int, int>>::value)
    {
      int xDis = abs(((pair<int, int>)state).first - ((pair<int, int>)(goalState->getState())).first);
      int yDis = abs(((pair<int, int>)state).second - ((pair<int, int>)(goalState->getState())).second);

      return (xDis + yDis)*1;
    }
    return 0;
  }
  State(T state1, string stateRe){
    state = state1;
    costToState = -1;
    prevState = nullptr;
    stateRepresentation = stateRe;
  }
  void setGoalState(State<T>* goalState1)
  {
    goalState = goalState1;
  }
  State<T>* getGoal()
  {
    return goalState;
  }
  bool equals(State& stateToCheck)
  {
    string h;
    return stateRepresentation == stateToCheck.getStateString();
  };
  T getState(){
    return state;
  }
  double getCost(){
    return costToState;
  }
  State<T>* getPrev()
  {
    return prevState;
  }
  void setCost(double newCost)
  {
    costToState = newCost;
  }
  void setPrev(State<T>* prev)
  {
    prevState = prev;
  }
  void setState(T state1)
  {
    state = state1;
  }
  string getStateString(){
    return stateRepresentation;
  }
  bool operator<(const State<T>& b) {
    return costToState < b.getCost();
  }
  State() {

  }
};

#endif //HW4_SEARCHALGORITHMS_STATE_H_
