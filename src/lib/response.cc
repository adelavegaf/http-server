#include <string>

#include "response.h"

namespace http {

std::string Response::ToString() {
  std::string output =
      protocol + " " + std::to_string(status_code) + " " + status_text + "\r\n";

  for (std::pair<std::string, std::string> i : headers) {
    output += i.first + ": " + i.second + "\r\n";
  }
  output += "\r\n";

  output += body;

  return output;
}

}  // namespace http