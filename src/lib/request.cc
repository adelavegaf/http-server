#include <string>

#include "method.h"
#include "request.h"

namespace http {

std::string Request::ToString() {
  std::string output =
      MethodToString(method) + " " + url + " " + protocol + "\r\n";

  for (std::pair<std::string, std::string> i : headers) {
    output += i.first + ": " + i.second + "\r\n";
  }
  output += "\r\n";

  output += body;

  return output;
}

}  // namespace http