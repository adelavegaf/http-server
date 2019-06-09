#include <string>

#include "response_builder.h"

namespace http {

ResponseBuilder::ResponseBuilder() {
  response.status_code = 200;
  response.protocol = "HTTP/1.1";
  response.status_text = "";
  response.body = "";
  response.headers["Connection"] = "keep-alive";
  response.headers["Server"] = "MyCPlusPlus";
}

ResponseBuilder& ResponseBuilder::SetStatus(int status_code,
                                            std::string status_text) {
  response.status_code = status_code;
  response.status_text = status_text;
  return *this;
}

ResponseBuilder& ResponseBuilder::SetBody(std::string body,
                                          std::string content_type) {
  response.body = body;
  response.headers["Content-Type"] = content_type;
  response.headers["Content-Length"] = std::to_string(body.length());
  return *this;
}

ResponseBuilder& ResponseBuilder::SetConnection(std::string connection) {
  response.headers["Connection"] = connection;
  return *this;
}

Response ResponseBuilder::Build() { return response; }

}  // namespace http
