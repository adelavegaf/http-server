#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http_server.h"

HttpServer::HttpServer(/* args */) {}

HttpServer::~HttpServer() {}

void HttpServer::Listen(int port) {
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

  char buffer[1024] = {0};
  read(new_socket, buffer, 1024);
  std::cout <<  buffer;
}
