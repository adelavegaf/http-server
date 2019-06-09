#ifndef HTTP_SERVER_SRC_LIB_REQUEST_H_
#define HTTP_SERVER_SRC_LIB_REQUEST_H_

#include <map>
#include <string>

#include "method.h"

namespace http {

struct RequestStatusLine {
  Method method;
  std::string url;
  std::string protocol;
};

struct Request {
  Method method;
  std::string url;
  std::string protocol;
  std::map<std::string, std::string> headers;
  std::string body;
  std::string ToString();
};

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_REQUEST_H_