#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_

#include <map>
#include <string>
#include "http_method.h"

using std::map;
using std::string;
using std::vector;

struct HttpHeader {
  Method method;
  string target;
  string version;
  map<string, string> optional;
};

struct HttpRequest {
  HttpHeader header;
  string body;
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_