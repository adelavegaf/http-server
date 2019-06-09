#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_

#include <optional>
#include <string>

#include "http_request.h"

using std::optional;
using std::string;

class RequestProcessor {
 public:
  RequestProcessor();
  optional<HttpRequest> Process(const char buffer[], int size);

 private:
  string cur_request;
  unsigned long GetContentLength(const string header);
  HttpRequest ParseRequest(const string header, const string body);
  RequestStatusLine ParseStatusLine(const string s);
  map<string, string> ParseHeaders(const vector<string> lines);
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_