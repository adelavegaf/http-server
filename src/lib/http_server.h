#ifndef HTTP_SERVER_SRC_LIB_HTTP_SERVER_H_
#define HTTP_SERVER_SRC_LIB_HTTP_SERVER_H_

#include <map>

#include "http_request.h"

namespace http {

typedef void (*HandlerFn)(HttpRequest req);

// Set up a server without using any libraries
// The server has to serve static content.
class HttpServer {
 public:
  HttpServer();
  ~HttpServer();
  void Listen(int port);
  void Handle(std::string path, HandlerFn handler);

 private:
  std::map<std::string, HandlerFn> handlers;
  void ConnectionHandler(int socket);
};

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_HTTP_SERVER_H_