//
// Created by matan on 1/15/20.
//

#include "MatrixSolverClientHandler.h"
#include "AStar.h"
#include <cstdlib>

#define SIZE_OF_BUFFER 4096

double* createMatrix(int size, string lines)
{
  string lineCopy = lines;
  double *matrix = new double[size];
  for(int i = 0; i < size; i++)
  {
    int currLoc = lineCopy.find_first_of(",\n");
    matrix[i] = atof(lineCopy.substr(0,currLoc).c_str());
    lineCopy = lineCopy.substr(currLoc+1);
  }
  return matrix;
}

int countNumberOfRows(string linesOfTable)
{
  int count = 0;
  for(char& c : linesOfTable) {
    if(c == '\n')
    {
      count++;
    }
  }

  return count + 1;
}

int countNumberOfColumns(string linesOfTable)
{
  int count = 0;
  for(char& c : linesOfTable) {
    if(c == ',')
    {
      count++;
    }
    if(c == '\n')
    {
      break;
    }
  }

  return count + 1;
}

string bufferToStringBig(char buffer[SIZE_OF_BUFFER])
{
  string output;
  for(int i = 0; i < 1024 && buffer[i] != '\0'; i++)
  {
    output += buffer[i];
  }

  return output;//+"\n";
}

void MatrixSolverClientHandler::handleClient(int inputStream, int outputStream) {
  bool end = false;
  pair<int, int> srcPoint;
  pair<int, int> dstPoint;
  int numOfRows;
  int numOfColumns;
  double* weightsMatrix;
  string problemName;

  ////////////////////////////////////////////////////
  //reading the lines from the client:
  string currLine;
  string linesOfTable;

  //reading from the client:
  char buffer[SIZE_OF_BUFFER] = {0};
  read( inputStream , buffer, SIZE_OF_BUFFER);

  linesOfTable += bufferToStringBig(buffer);

  //reading the table:
  while(!end)
  {
    //reading from the client:
    char buffer[SIZE_OF_BUFFER] = {0};
    read( inputStream , buffer, SIZE_OF_BUFFER);

    linesOfTable += bufferToStringBig(buffer);
    if(!needToEnd(linesOfTable)) {
      linesOfTable += currLine;
    }
    else
    {
      end = true;
    }
  }

  ////////////////////////////////////////////////////
  //parsing the lines to get the src and dst points:
  linesOfTable = linesOfTable.substr(0, linesOfTable.length() - 5);
  problemName = linesOfTable;

  string dst = linesOfTable.substr(linesOfTable.find_last_of('\n')+1);
  linesOfTable = linesOfTable.substr(0, linesOfTable.find_last_of('\n'));

  string src = linesOfTable.substr(linesOfTable.find_last_of('\n')+1);
  linesOfTable = linesOfTable.substr(0, linesOfTable.find_last_of('\n'));

  //getting the source and destination points:
  srcPoint = pair<int, int>(atoi(src.substr(0, src.find(',')).c_str()), atoi(src.substr(src.find(',')+1).c_str()));
  dstPoint = pair<int, int>(atoi(dst.substr(0, dst.find(',')).c_str()), atoi(dst.substr(dst.find(',')+1).c_str()));

  //getting the dimensions of the matrix:
  numOfRows = countNumberOfRows(linesOfTable);
  numOfColumns = countNumberOfColumns(linesOfTable);

  //getting the weight matrix:
  weightsMatrix = createMatrix(numOfColumns*numOfColumns, linesOfTable);


  //creating the matrix problem:
  ISearchable<pair<int, int>>* problem = new MatrixGraphProblem(srcPoint, dstPoint, numOfRows, numOfColumns, reinterpret_cast<double *>(weightsMatrix));

  string solutionToSend;
  if((MatrixSolverClientHandler::cache)->doesSolutionExists(problemName))
  {
    solutionToSend = (MatrixSolverClientHandler::cache)->returnSolution(problemName);
  }
  else
  {
    solutionToSend = (MatrixSolverClientHandler::algSolver)->solve(problem);
    (MatrixSolverClientHandler::cache)->saveSolution(problemName, solutionToSend);
  }

  int is_sent = send(inputStream , (solutionToSend).c_str() , strlen((solutionToSend).c_str()) , 0 );
  if (is_sent == -1) {
    std::cout<<"Error sending message"<<std::endl;
  }
}

MatrixSolverClientHandler::MatrixSolverClientHandler(Solver<ISearchable<pair<int, int>>*, string> *solver,
                                                     CacheManager *cacheManager) {
  MatrixSolverClientHandler::algSolver = solver;
  MatrixSolverClientHandler::cache = cacheManager;
}

bool MatrixSolverClientHandler::needToEnd(string stringToCheck) {
  return stringToCheck.length() >= 4 && stringToCheck.substr(stringToCheck.length() - 4) == "end\n";
}
MatrixSolverClientHandler *MatrixSolverClientHandler::clone() {
  new MatrixSolverClientHandler(algSolver->clone(), cache->clone());
}
