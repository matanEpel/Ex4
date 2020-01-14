//
// Created by matan on 1/10/20.
//

#ifndef HW4__FILECACHEMANAGER_H_
#define HW4__FILECACHEMANAGER_H_

#include "interfaces.h"

class FileCacheManager : public CacheManager{
 public:
  bool doesSolutionExists(string problem) override;
  string returnSolution(string problem) override;
  void saveSolution(string problem, string solution) override;
};

#endif //HW4__FILECACHEMANAGER_H_
