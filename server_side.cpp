//
// Created by matan on 1/10/20.
//

#include "server_side.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "../searchAlgorithms/MatrixSolverClientHandler.h"
#include "../searchAlgorithms/AStar.h"
#include "ISearcherSolverAdapter.h"
#include "MyParallelServer.h"
#include "../searchAlgorithms/BestFirstSearch.h"
#include "../searchAlgorithms/BFS.h"
#include "../searchAlgorithms/DFS.h"

void boot::Main::main(int port) const {

  ISearcher<pair<int, int>>* aStarSearcher= new AStar<pair<int, int>>();
  Solver<ISearchable<pair<int, int>>*, string>* solver = new ISearcherSolverAdopter(aStarSearcher);
  CacheManager* cache = new FileCacheManager();
  Server* server = new MyParallelServer();
  ClientHandler* clientHandler = new MatrixSolverClientHandler(solver, cache);

  thread mainThread([=] {server->open(port, clientHandler); });

  //giving the server a 30-seconds lifetime:
 // sleep(30);
//  server->close();

  mainThread.join();
}
