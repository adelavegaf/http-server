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
  // Header attributes
  StatusLine status_line;
  map<string, string> optional_headers;
  string body;
  StatusLine GetStatusLine(string s);
  map<string, string> GetOptionalHeaders(vector<string> lines);
  Method StringToHttpMethod(string m);

 public:
  HttpRequest(string r);
  ~HttpRequest();
};
#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_H_