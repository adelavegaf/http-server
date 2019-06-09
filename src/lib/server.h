#ifndef HTTP_SERVER_SRC_LIB_SERVER_H_
#define HTTP_SERVER_SRC_LIB_SERVER_H_

#include <map>

#include "request.h"
#include "response.h"

namespace http {

typedef Response (*HandlerFn)(Request req);

// Set up a server without using any libraries
// The server has to serve static content.
class Server {
 public:
  Server();
  ~Server();
  void Listen(int port);
  void Handle(std::string path, HandlerFn handler);

 private:
  std::map<std::string, HandlerFn> handlers;
  void ConnectionHandler(int socket);
  Response GetDefaultErrorResponse();
};

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_SERVER_H_