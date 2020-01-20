//
// Created by matan on 1/19/20.
//

#ifndef HW4_SERVER_MYPARALLELSERVER_H_
#define HW4_SERVER_MYPARALLELSERVER_H_

#include "interfaces.h"
class MyParallelServer : public Server{
 public:
  void open(int port, ClientHandler* clientHandler) override;
  void closeS() override;
};

#endif //HW4_SERVER_MYPARALLELSERVER_H_
