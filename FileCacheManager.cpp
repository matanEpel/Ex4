//
// Created by matan on 1/10/20.
//

#include <fstream>
#include "FileCacheManager.h"
void FileCacheManager::saveSolution(string problem, string solution) {
  try{
    ofstream fileStream;
    fileStream.exceptions(ifstream::failbit); //making exceptions to occur;
    //opening the file:
    fileStream.open(problem, ios::app);
    if(fileStream)
    {
      fileStream<<solution;
    }
    else
    {
      throw "Error with opening the file";
    }
  }
  catch (...) {
    throw "error opening the file";
  }
}

string FileCacheManager::returnSolution(string problem) {
  string solution;
  try{
    ifstream fileStream;
    fileStream.exceptions(ifstream::failbit); //making exceptions to occur;
    //opening the file:
    fileStream.open(problem);
    if(fileStream)
    {
      getline(fileStream,solution);
    }
    else
    {
      throw "Error with opening the file";
    }
  }
  catch (...) {
    throw "error opening the file";
  }

  return solution;
}

bool FileCacheManager::doesSolutionExists(string problem) {
  //checking if file exists:
  FILE* file1;
  file1 = fopen(problem.c_str(), "r");
  if(file1)
  {
    fclose(file1);
    return true;
  }
  else
  {
    return false;
  }
}
