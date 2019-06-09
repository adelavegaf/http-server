#include "lib/http_server.h"

int main() {
  http::HttpServer server;
  server.Listen(8080);
}