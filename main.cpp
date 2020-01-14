
#include "interfaces.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "server_side.h"

using namespace boot;

int main(int argc, char const *argv[]) {
  int port = atoi(argv[1]);

  Main mainRun;
  mainRun.main(port);
  return 0;
}