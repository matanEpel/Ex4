//
// Created by matan on 1/10/20.
//

#ifndef HW4__MYTESTCLIENTHANDLER_H_
#define HW4__MYTESTCLIENTHANDLER_H_

#include "interfaces.h"

class MyTestClientHandler : public ClientHandler{
 private:
  Solver<string, string>* algSolver;
  CacheManager* cache;

 public:
  explicit MyTestClientHandler(Solver<string, string>* solver, CacheManager* cacheManager);
  void handleClient(int inputStream, int outputStream) override;
};

#endif //HW4__MYTESTCLIENTHANDLER_H_
