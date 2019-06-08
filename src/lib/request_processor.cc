#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "http_request.h"
#include "request_processor.h"

using std::map;
using std::optional;
using std::string;

RequestProcessor::RequestProcessor() { cur_request = ""; }

optional<HttpRequest> RequestProcessor::Process(const char buffer[], int size) {
  for (int i = 0; i < size; i++) {
    cur_request += buffer[i];
  }

  string header_end_key = "\r\n\r\n";
  auto header_end_pos = cur_request.find(header_end_key);

  if (header_end_pos == string::npos) {
    // We have not reached the end of the header marked by two consecutive \r\n.
    return std::nullopt;
  }

  // header will include \r\n\r\n
  string header =
      cur_request.substr(0, header_end_pos + header_end_key.length());

  auto body_byte_count = cur_request.length() - header.length();
  auto bytes_in_body = GetContentLength(header);

  if (body_byte_count < bytes_in_body) {
    // We are missing some bytes from the request's body.
    return std::nullopt;
  }

  string body = cur_request.substr(header.length(), bytes_in_body);
  cur_request =
      cur_request.substr(header.length() + bytes_in_body, string::npos);

  HttpRequest req = ParseRequest(header, body);
  return {req};
}

unsigned long RequestProcessor::GetContentLength(string header) {
  string key = "Content-Length: ";
  auto key_pos = header.find(key);
  if (key_pos == string::npos) {
    return 0;
  }
  auto end_pos = header.find("\r\n", key_pos);
  auto start_pos = key_pos + key.length();
  string content_length_str = header.substr(start_pos, end_pos - start_pos);
  return std::stoul(content_length_str);
}

HttpRequest RequestProcessor::ParseRequest(string header_str, string body_str) {
  auto header = ParseHeader(header_str);
  return {header, body_str};
}

HttpHeader RequestProcessor::ParseHeader(string header) {
  size_t start_pos = 0;
  vector<string> lines;
  string delimiter = "\r\n";
  while (true) {
    size_t pos = header.find(delimiter, start_pos);
    if (pos == string::npos || start_pos == pos) {
      // start_pos and pos will only be the equal when start_pos is pointing
      // to the last \r\n.
      break;
    }
    lines.push_back(header.substr(start_pos, pos - start_pos));
    start_pos = pos + delimiter.length();
  }

  auto status_line = ParseStatusLine(lines[0]);
  auto optional_headers = ParseOptionalHeaders(lines);

  return {status_line.method, status_line.target, status_line.version,
          optional_headers};
}

StatusLine RequestProcessor::ParseStatusLine(string s) {
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

map<string, string> RequestProcessor::ParseOptionalHeaders(
    vector<string> lines) {
  map<string, string> opt_headers;
  for (int i = 1; i < lines.size() - 1; i++) {
    int separator = lines[i].find(": ");
    string key = lines[i].substr(0, separator);
    string value = lines[i].substr(separator + 2, string::npos);
    opt_headers[key] = value;
  }
  return opt_headers;
}