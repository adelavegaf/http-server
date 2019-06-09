#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_

#include <optional>
#include <string>

#include "request.h"

namespace http {

class RequestProcessor {
 public:
  RequestProcessor();
  std::optional<Request> Process(const char buffer[], int size);

 private:
  std::string cur_request;
  unsigned long GetContentLength(const std::string header);
  Request ParseRequest(const std::string header, const std::string body);
  RequestStatusLine ParseStatusLine(const std::string s);
  std::map<std::string, std::string> ParseHeaders(
      const std::vector<std::string> lines);
};

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_
