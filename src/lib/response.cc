#include <string>

#include "response.h"

namespace http {

std::string Response::ToString() {
  std::string output =
      protocol + " " + std::to_string(status_code) + " " + status_text + "\r\n";

  for (std::pair<std::string, std::string> i : headers) {
    output += i.first + ": " + i.second + "\r\n";
  }
  output += "\r\n";

  output += body;

  return output;
}

Response::Builder::Builder() {
  response.status_code = 200;
  response.protocol = "HTTP/1.1";
  response.status_text = "";
  response.body = "";
  response.headers["Connection"] = "keep-alive";
  response.headers["Server"] = "MyCPlusPlus";
}

Response::Builder& Response::Builder::SetStatus(int status_code,
                                                std::string status_text) {
  response.status_code = status_code;
  response.status_text = status_text;
  return *this;
}

Response::Builder& Response::Builder::SetBody(std::string body,
                                              std::string content_type) {
  response.body = body;
  response.headers["Content-Type"] = content_type;
  response.headers["Content-Length"] = std::to_string(body.length());
  return *this;
}

Response::Builder& Response::Builder::SetConnection(std::string connection) {
  response.headers["Connection"] = connection;
  return *this;
}

Response Response::Builder::Build() { return response; }

}  // namespace http