#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_

#include <optional>
#include <string>

#include "http_request.h"

using std::optional;
using std::string;

struct StatusLine {
  Method method;
  string target;
  string version;
};

class RequestProcessor {
 public:
  RequestProcessor();
  optional<HttpRequest> Process(const char buffer[], int size);

 private:
  string cur_request;
  unsigned long GetContentLength(string header);
  HttpRequest ParseRequest(string header, string body);
  HttpHeader ParseHeader(string header);
  StatusLine ParseStatusLine(string s);
  map<string, string> ParseOptionalHeaders(vector<string> lines);
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_