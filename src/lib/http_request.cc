#include <string>

#include "http_method.h"
#include "http_request.h"

namespace http {

std::string HttpRequest::ToString() {
  std::string output =
      HttpMethodToString(method) + " " + url + " " + protocol + "\r\n";

  for (std::pair<std::string, std::string> i : headers) {
    output += i.first + ": " + i.second + "\r\n";
  }
  output += "\r\n";

  output += body;

  return output;
}

}  // namespace http