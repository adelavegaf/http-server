#ifndef HTTP_SERVER_SRC_LIB_RESPONSE_BUILDER_H_
#define HTTP_SERVER_SRC_LIB_RESPONSE_BUILDER_H_

#include <map>

#include "response.h"

namespace http {

class ResponseBuilder {
 public:
  ResponseBuilder();
  ResponseBuilder& SetStatus(int status_code, std::string status_text);
  ResponseBuilder& SetBody(std::string body, std::string content_type);
  ResponseBuilder& SetConnection(std::string connection);
  Response Build();

 private:
  Response response;
  std::map<std::string, std::string> headers;
};

}  // namespace http
#endif  // HTTP_SERVER_SRC_LIB_RESPONSE_BUILDER_H_