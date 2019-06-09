#include "lib/request.h"
#include "lib/response.h"
#include "lib/server.h"

int main() {
  http::Server server;
  server.Handle("/test", [](http::Request) -> http::Response {
    http::Response r;
    r.status_code = 200;
    r.status_text = "Ok";
    r.protocol = "HTTP/1.1";
    r.body = "Handler was registered!";

    std::map<std::string, std::string> headers;
    headers["Connection"] = "keep-alive";
    headers["Content-Type"] = "text/html";
    headers["Content-Length"] = std::to_string(r.body.length());
    r.headers = headers;

    return r;
  });
  server.Listen(8080);
}