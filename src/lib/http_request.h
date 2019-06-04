#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_

#include <map>
#include <string>
#include "http_method.h"

using std::map;
using std::string;
using std::vector;

struct StatusLine {
  Method method;
  string uri;
  string version;
};

class HttpRequest {
 private:
  StatusLine status_line;
  map<string, string> optional_headers;
  StatusLine GetStatusLine(string s);
  map<string, string> GetOptionalHeaders(vector<string> lines);
  Method StringToHttpMethod(string m);
  string body;

 public:
  HttpRequest(string r);
  ~HttpRequest();
  Method GetMethod();
};
#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_