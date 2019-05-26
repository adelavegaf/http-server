#include "lib/http_server.h"

int main() {
  HttpServer server;
  server.Listen(8080);
}