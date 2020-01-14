//
// Created by matan on 1/14/20.
//

#ifndef HW4__STRINGREVERSER_H_
#define HW4__STRINGREVERSER_H_

#include <string>
#include "interfaces.h"
#include<bits/stdc++.h>

using namespace std;

 class StringReverser : public Solver<string, string>{
  public:
   string solve(string problem) override;
};

#endif //HW4__STRINGREVERSER_H_
