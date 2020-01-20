//
// Created by matan on 1/15/20.
//

#ifndef HW4_SEARCHALGORITHMS_MATRIXSOLVERCLIENTHANDLER_H_
#define HW4_SEARCHALGORITHMS_MATRIXSOLVERCLIENTHANDLER_H_

#include "../server/interfaces.h"
#include "MatrixGraphProblem.h"

class MatrixSolverClientHandler : public ClientHandler {

  Solver<ISearchable<pair<int, int>>*, string>* algSolver;
  CacheManager* cache;
 public:
  void handleClient(int inputStream, int outputStream) override;
  explicit MatrixSolverClientHandler(Solver<ISearchable<pair<int, int>>*, string>* solver, CacheManager* cacheManager);
  bool needToEnd(string stringToCheck);
  MatrixSolverClientHandler* clone() override;
};

#endif //HW4_SEARCHALGORITHMS_MATRIXSOLVERCLIENTHANDLER_H_
