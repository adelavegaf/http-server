#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "http_server.h"

HttpServer::HttpServer(/* args */)
{
}

HttpServer::~HttpServer()
{
}

void HttpServer::Listen(int port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = port;

  if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  const int backlog = 3;

  if (listen(sockfd, backlog) < 0) {
    perror("listening failed");
    exit(EXIT_FAILURE);
  }

  int new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t *) sizeof(address));

  if (new_socket < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }

  char buffer[1024] = {0}; 
  read(new_socket, buffer, 1024);
  printf("%s\n",buffer );
}
