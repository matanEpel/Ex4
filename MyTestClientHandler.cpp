//
// Created by matan on 1/10/20.
//

#include <iostream>
#include "MyTestClientHandler.h"

string bufferToString(char buffer[1024])
{
  string output = "";
  for(int i = 0; i < 1024 && buffer[i] != '\0'; i++)
  {
    output += buffer[i];
  }

  return output;
}

void MyTestClientHandler::handleClient(int inputStream, int outputStream) {
  //int inputStream = client socket, int outputStream = server socket
  bool end = false;

  while(!end)
  {
    //reading from the client:
    char buffer[1024] = {0};
    read( inputStream , buffer, 1024);
    buffer[1023] = '\0';
    buffer[strlen(buffer)-1]= '\0';

    string problem = bufferToString(buffer);
    if(strcmp(buffer, "end") != 0)
    {
      string solution;
      if((MyTestClientHandler::cache)->doesSolutionExists(problem))
      {
        solution = (MyTestClientHandler::cache)->returnSolution(problem);
      }
      else
      {
        solution = (MyTestClientHandler::algSolver)->solve(problem);
        (MyTestClientHandler::cache)->saveSolution(problem, solution);
      }
      int is_sent = send(inputStream , (solution).c_str() , strlen((solution).c_str()) , 0 );
      if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
      }
    }
    else
    {
      end = true;
    }
  }
}

MyTestClientHandler::MyTestClientHandler(Solver<string, string>* solver, CacheManager* cacheManager) {
  MyTestClientHandler::algSolver = solver;
  MyTestClientHandler::cache = cacheManager;

}
