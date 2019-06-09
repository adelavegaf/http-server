#include <string>

#include "http_response.h"

using std::string;

string HttpResponse::ToString() {
  string output =
      protocol + " " + std::to_string(status_code) + " " + status_text + "\r\n";

  for (std::pair<string, string> i : headers) {
    output += i.first + ": " + i.second + "\r\n";
  }
  output += "\r\n";

  output += body;

  return output;
}