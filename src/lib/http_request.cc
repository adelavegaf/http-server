#include <string>

#include "http_method.h"
#include "http_request.h"

string HttpRequest::ToString() {
  string output = http_method::HttpMethodToString(method) + " " + url + " " +
                  protocol + "\r\n";

  for (std::pair<string, string> i : headers) {
    output += i.first + ": " + i.second + "\r\n";
  }
  output += "\r\n";

  output += body;

  return output;
}