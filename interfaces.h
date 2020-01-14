//
// Created by matan on 1/14/20.
//

#ifndef HW4__INTERFACES_H_
#define HW4__INTERFACES_H_

#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

template<typename Problem, typename  Solution> class Solver {
 public:
  virtual Solution solve(Problem problem) = 0;
};

class CacheManager {
 public:
  virtual bool doesSolutionExists(string problem) = 0;
  virtual string returnSolution(string problem) = 0;
  virtual void saveSolution(string problem, string solution) = 0;
};

class ClientHandler {
 public:
  virtual void handleClient(int inputStream, int outputStream) = 0;
};

class Server {
 protected:
  bool needToClose;
 public:
  virtual void open(int port, ClientHandler* clientHandler) = 0;
  virtual void close() = 0;
};

#endif //HW4__INTERFACES_H_
