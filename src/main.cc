#include "lib/request.h"
#include "lib/response.h"
#include "lib/server.h"

int main() {
  http::Server server;
  server.Handle("/test", [](http::Request) -> http::Response {
    return http::Response::Builder{}
        .SetStatus(200, "ok")
        .SetBody("Handler was registered!", "text/html")
        .Build();
  });
  server.Listen(8080);
}