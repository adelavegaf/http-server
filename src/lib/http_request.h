#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_

#include <map>
#include <string>
#include "http_method.h"

using std::map;
using std::string;
using std::vector;

struct RequestStatusLine {
  Method method;
  string url;
  string protocol;
};

struct HttpRequest {
  Method method;
  string url;
  string protocol;
  map<string, string> headers;
  string body;
  string ToString();
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_