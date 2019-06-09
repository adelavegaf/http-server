#ifndef HTTP_SERVER_SRC_LIB_HTTP_RESPONSE_H_
#define HTTP_SERVER_SRC_LIB_HTTP_RESPONSE_H_

#include <map>
#include <string>
#include "http_method.h"

using std::map;
using std::string;
using std::vector;

struct ResponseStatusLine {
  string protocol;
  int status_code;
  string status_text;
};

struct HttpResponse {
  string protocol;
  int status_code;
  string status_text;
  map<string, string> headers;
  string body;
  string ToString();
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_RESPONSE_H_