//
// Created by matan on 1/10/20.
//

#ifndef HW4__MYSERIALSERVER_H_
#define HW4__MYSERIALSERVER_H_

#include "interfaces.h"

class MySerialServer : public Server{
 public:
  void open(int port, ClientHandler* clientHandler) override;
  void closeS() override;
};

#endif //HW4__MYSERIALSERVER_H_
