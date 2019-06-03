#ifndef HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_
#define HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class RequestProcessor {
 public:
  void Process(const char buffer[], int size);

 private:
  string cur_request;
  int GetContentLength(string request);
};

#endif  // HTTP_SERVER_SRC_LIB_HTTP_REQUEST_PROCESSOR_H_