#include "http_request.h"

#include <iostream>
#include <string>
#include <vector>

#include "http_method.h"

using std::string;
using std::vector;

HttpRequest::HttpRequest(string r) {
  size_t start_pos = 0;
  vector<string> lines;
  string delimiter = "\r\n";
  while (true) {
    size_t pos = r.find(delimiter, start_pos);
    if (pos == string::npos || start_pos + delimiter.length() == pos) {
      // Two consecutive \r\n mark the end of the header.
      break;
    }
    lines.push_back(r.substr(start_pos, pos - start_pos));
    start_pos = pos + delimiter.length();
  }

  if (lines.size() == 0) {
    return;
  }

  body = r.length() > start_pos + delimiter.length()
             ? r.substr(start_pos + delimiter.length(), string::npos)
             : "";

  status_line = GetStatusLine(lines[0]);
  optional_headers = GetOptionalHeaders(lines);
}

StatusLine HttpRequest::GetStatusLine(string s) {
  size_t start_pos = 0;
  size_t next_pos = s.find(" ", start_pos);
  string m = s.substr(start_pos, next_pos);
  Method method = stringToHttpMethod(m);

  start_pos = next_pos + 1;
  next_pos = s.find(" ", start_pos);
  string uri = s.substr(start_pos, next_pos - start_pos);

  string version = s.substr(next_pos + 1, string::npos);

  return {method, uri, version};
}

map<string, string> HttpRequest::GetOptionalHeaders(vector<string> lines) {
  map<string, string> opt_headers;
  for (int i = 1; i < lines.size() - 1; i++) {
    int separator = lines[i].find(": ");
    string key = lines[i].substr(0, separator);
    string value = lines[i].substr(separator + 2, string::npos);
    opt_headers[key] = value;
  }
  return opt_headers;
}

HttpRequest::~HttpRequest() {}