#ifndef HTTP_SERVER_SRC_LIB_RESPONSE_H_
#define HTTP_SERVER_SRC_LIB_RESPONSE_H_

#include <map>
#include <string>

namespace http {

struct ResponseStatusLine {
  std::string protocol;
  int status_code;
  std::string status_text;
};

struct Response {
  class Builder;
  std::string protocol;
  int status_code;
  std::string status_text;
  std::map<std::string, std::string> headers;
  std::string body;
  std::string ToString();
};

class Response::Builder {
 public:
  Builder();
  Response::Builder& SetStatus(int status_code, std::string status_text);
  Response::Builder& SetBody(std::string body, std::string content_type);
  Response::Builder& SetConnection(std::string connection);
  Response Build();

 private:
  Response response;
};

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_RESPONSE_H_