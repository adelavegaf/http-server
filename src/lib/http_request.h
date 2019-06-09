#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_

#include <map>
#include <string>

#include "http_method.h"

namespace http {

struct RequestStatusLine {
  Method method;
  std::string url;
  std::string protocol;
};

struct HttpRequest {
  Method method;
  std::string url;
  std::string protocol;
  std::map<std::string, std::string> headers;
  std::string body;
  std::string ToString();
};

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_