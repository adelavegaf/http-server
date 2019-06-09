#include "lib/server.h"

int main() {
  http::Server server;
  server.Listen(8080);
}