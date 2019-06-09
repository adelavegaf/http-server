#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <map>

#include "request.h"
#include "request_processor.h"
#include "response.h"
#include "response_builder.h"
#include "server.h"

namespace http {

Server::Server() {}

Server::~Server() {}

void Server::Handle(std::string path, HandlerFn handler) {
  std::cout << "Registering handler for path " << path << std::endl;
  handlers[path] = handler;
}

void Server::Listen(int port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  int opt = 1;

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  int addrlen = sizeof(address);

  if (bind(sockfd, (struct sockaddr *)&address, addrlen) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  const int backlog = 1;

  if (listen(sockfd, backlog) < 0) {
    perror("listening failed");
    exit(EXIT_FAILURE);
  }

  std::cout << "accepting new connections" << std::endl;

  int new_socket =
      accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

  if (new_socket < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }

  std::cout << "received connection" << std::endl;
  ConnectionHandler(new_socket);
}

void Server::ConnectionHandler(int socket) {
  const int buffer_size = 1024;
  int bytes_read;
  char buffer[buffer_size] = {0};
  RequestProcessor rp;

  // TODO(adelavega): blocks unless socket is closed. Set a timeout?
  while ((bytes_read = read(socket, buffer, buffer_size)) > 0) {
    std::cout << "read " << bytes_read << " bytes" << std::endl;
    std::cout << buffer << std::endl;
    auto req = rp.Process(buffer, bytes_read);
    if (!req) {
      continue;
    }

    std::string path = req->url;
    Response r;

    if (handlers.count(path) == 0) {
      std::cout << "No registered handlers for path: " << path << std::endl;
      r = GetDefaultErrorResponse();
    } else {
      std::cout << "Handler for path found: " << path << std::endl;
      r = handlers[path](*req);
    }
    const char *response = r.ToString().c_str();

    std::cout << "Sending response" << std::endl << std::endl;
    std::cout << response << std::endl << std::endl;

    if (send(socket, response, strlen(response), 0) == -1) {
      std::cout << "Failed to send response" << std::endl;
      perror("send failed");
      close(socket);
      break;
    }
  }
}

Response Server::GetDefaultErrorResponse() {
  return ResponseBuilder{}
      .SetStatus(404, "Not found")
      .SetConnection("Closed")
      .SetBody("Not found", "text/html")
      .Build();
}

}  // namespace http