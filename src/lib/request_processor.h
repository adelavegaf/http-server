#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_

#include <optional>
#include <string>

#include "http_request.h"

using std::optional;
using std::string;

class RequestProcessor {
 public:
  optional<HttpRequest> Process(const char buffer[], int size);
  StatusLine GetStatusLine();

 private:
  string cur_request;
  optional<unsigned long> GetContentLength(string header);
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_