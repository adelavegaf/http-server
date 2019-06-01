// Set up a server without using any libraries
// The server has to serve HTML, CSS and JS content.
// Implement a router from scratch
// Watch for changes and refresh the server

class HttpServer {
 public:
  HttpServer(/* args */);
  ~HttpServer();
  void Listen(int port);

 private:
  void ConnectionHandler(int socket);
};
