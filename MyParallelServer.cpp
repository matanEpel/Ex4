//
// Created by matan on 1/19/20.
//

#include <thread>
#include <vector>
#include "MyParallelServer.h"
#define TIME_OUT_LENGTH 120

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
  Server::needToClose = false;
  // Create a vector of threads
  std::vector<std::thread> vecOfThreads;
  int client_socket;
  //create socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    //error
    std::cerr << "Could not create a socket"<<std::endl;
  }

  //timeout:
  struct timeval tv;
  tv.tv_sec = TIME_OUT_LENGTH;
  setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
  int iSetOption = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof(iSetOption));

  //bind socket to IP address
  // we first need to create the sockaddr obj.
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
  address.sin_port = htons(port);
  //we need to convert our number
  // to a number that the network understands.

  //the actual bind command
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    std::cerr<<"Could not bind the socket to an IP"<<std::endl;
  }

  //timing taken from https://https://stackoverflow.com/questions/39971780/c-second-counter/39972473#39972473.com/questions/33065568/a-time-counter-in-c
  auto start = std::chrono::high_resolution_clock::now();

  int i = 1;
  while(!needToClose)
  {
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
      std::cerr<<"Error during listening command"<<std::endl;
    } else{
      std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    client_socket = accept(socketfd, (struct sockaddr *)&address,
                           (socklen_t*)&address);

    if (client_socket == -1) {
      std::cerr<<"Timeout!!"<<std::endl;
    }
    else
    {
      ClientHandler* copyHandler = clientHandler->clone();
      vecOfThreads.emplace_back(&ClientHandler::handleClient, copyHandler, client_socket, socketfd); //socketfd is the server socket
      i++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    if(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()  >= TIME_OUT_LENGTH)
    {
      closeS();
    }
  }

  // Iterate over the thread vector
  for (std::thread & th : vecOfThreads)
  {
    // If thread Object is Joinable then Join that thread.
    if (th.joinable())
      th.join();
  }

  close(client_socket);
  close(socketfd);
}
void MyParallelServer::closeS() {
  Server::needToClose = true;
}
