
#include "searchAlgorithms/MatrixGraphProblem.h"
#include "server/server_side.h"

using namespace boot;

int main(int argc, char const *argv[])
{
  int port = 5400;//atoi(argv[1]);
  Main mainRun;
  mainRun.main(port);


  return 0;
}