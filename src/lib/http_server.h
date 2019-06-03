#ifndef HTTP_SERVER_SRC_LIB_HTTP_SERVER_H_
#define HTTP_SERVER_SRC_LIB_HTTP_SERVER_H_

// Set up a server without using any libraries
// The server has to serve static content.
class HttpServer {
 public:
  HttpServer(/* args */);
  ~HttpServer();
  void Listen(int port);

 private:
  void ConnectionHandler(int socket);
};
#endif  // HTTP_SERVER_SRC_LIB_HTTP_SERVER_H_