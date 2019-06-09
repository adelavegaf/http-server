#ifndef HTTP_SERVER_SRC_LIB_HTTP_RESPONSE_H_
#define HTTP_SERVER_SRC_LIB_HTTP_RESPONSE_H_

#include <map>
#include <string>
#include "http_method.h"

namespace http {

struct ResponseStatusLine {
  std::string protocol;
  int status_code;
  std::string status_text;
};

struct HttpResponse {
  std::string protocol;
  int status_code;
  std::string status_text;
  std::map<std::string, std::string> headers;
  std::string body;
  std::string ToString();
};

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_HTTP_RESPONSE_H_