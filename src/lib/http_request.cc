#include "http_request.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

HttpRequest::HttpRequest(string r) {
  size_t start_pos = 0;
  vector<string> lines;
  while (true) {
    size_t pos = r.find("\r\n", start_pos);
    if (pos == string::npos) {
      break;
    }
    lines.push_back(r.substr(start_pos, pos - start_pos));
    start_pos = pos + 1;
  }

  if (lines.size() == 0) {
    return;
  }

  // Parse Status-Line
  string req_line = lines[0];

  start_pos = 0;
  size_t next_pos = req_line.find(" ", start_pos);
  string m = req_line.substr(start_pos, next_pos);
  method = StringToHttpMethod(m);

  start_pos = next_pos + 1;
  next_pos = req_line.find(" ", start_pos);
  uri = req_line.substr(start_pos, next_pos - start_pos);

  version = req_line.substr(next_pos + 1, string::npos);

  // Parse Key-Value pairs
  for (int i = 1; i < lines.size() - 1; i++) {
    int separator = lines[i].find(": ");
    string key = lines[i].substr(0, separator);
    string value = lines[i].substr(separator + 2, string::npos);
    std::cout << key << " -> " << value << std::endl;
    optional_headers[key] = value;
  }
}

HttpRequest::~HttpRequest() {}

Method HttpRequest::StringToHttpMethod(string m) {
  std::transform(m.begin(), m.end(), m.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  if (m == "GET") {
    return Method::GET;
  } else if (m == "POST") {
    return Method::POST;
  } else if (m == "PUT") {
    return Method::PUT;
  } else if (m == "DELETE") {
    return Method::DELETE;
  } else if (m == "OPTIONS") {
    return Method::OPTIONS;
  } else if (m == "HEAD") {
    return Method::HEAD;
  } else if (m == "CONNECT") {
    return Method::CONNECT;
  } else if (m == "TRACE") {
    return Method::TRACE;
  } else {
    return Method::UNKNOWN;
  }
}