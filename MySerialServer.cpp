//
// Created by matan on 1/10/20.
//

#include <iostream>
#include "MySerialServer.h"

#define TIME_OUT_LENGTH 120
void MySerialServer::open(int port, ClientHandler* clientHandler) {
  MySerialServer::needToClose = false;
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
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (client_socket == -1) {
      std::cerr<<"Error accepting client"<<std::endl;
    }

    clientHandler->handleClient(client_socket, socketfd); //socketfd is the server socket
    i++;
  }
  shutdown(socketfd, 2);
}

void MySerialServer::close() {
  MySerialServer::needToClose = true;
}
