#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_

#include <optional>
#include <string>
#include <vector>

#include "http_request.h"

using std::string;
using std::vector;

class RequestProcessor {
 public:
  std::optional<HttpRequest> Process(const char buffer[], int size);
  StatusLine GetStatusLine();

 private:
  string cur_request;
  int GetContentLength(string request);
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_