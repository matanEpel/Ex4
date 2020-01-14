//
// Created by matan on 1/10/20.
//

#include "server_side.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"

void boot::Main::main(int port) const {

  Solver<string, string>* solver = new StringReverser();
  CacheManager* cache = new FileCacheManager();
  Server* server = new MySerialServer();
  ClientHandler* clientHandler = new MyTestClientHandler(solver, cache);

  thread mainThread([=] {server->open(port, clientHandler); });

  //giving the server a 30-seconds lifetime:
  sleep(30);
  server->close();
  
  mainThread.join();
}
