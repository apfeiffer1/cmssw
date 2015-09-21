
#include "../src/CondSimpleHTTPClient.h"

int
main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " url" << std::endl;
    return 1;
  }

  return cond::simpleHTTPClient( argv[1] );

}
