#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "http_request.h"
#include "request_processor.h"

using http_method::Method;
using http_method::StringToHttpMethod;
using std::map;
using std::optional;
using std::string;

RequestProcessor::RequestProcessor() { cur_request = ""; }

optional<HttpRequest> RequestProcessor::Process(const char buffer[],
                                                const int size) {
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

unsigned long RequestProcessor::GetContentLength(const string header) {
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

HttpRequest RequestProcessor::ParseRequest(const string header,
                                           const string body) {
  size_t start_pos = 0;
  vector<string> lines;
  string delimiter = "\r\n";

  while (true) {
    size_t pos = header.find(delimiter, start_pos);
    if (pos == string::npos || start_pos == pos) {
      // start_pos and pos will only be equal when start_pos is pointing to the
      // last \r\n.
      break;
    }
    lines.push_back(header.substr(start_pos, pos - start_pos));
    start_pos = pos + delimiter.length();
  }

  auto sl = ParseStatusLine(lines[0]);
  auto headers = ParseHeaders(lines);

  return {sl.method, sl.url, sl.protocol, headers, body};
}

RequestStatusLine RequestProcessor::ParseStatusLine(const string s) {
  size_t start_pos = 0;
  size_t next_pos = s.find(" ", start_pos);
  string m = s.substr(start_pos, next_pos);
  Method method = StringToHttpMethod(m);

  start_pos = next_pos + 1;
  next_pos = s.find(" ", start_pos);
  string url = s.substr(start_pos, next_pos - start_pos);

  string protocol = s.substr(next_pos + 1, string::npos);

  return {method, url, protocol};
}

map<string, string> RequestProcessor::ParseHeaders(const vector<string> lines) {
  map<string, string> headers;
  for (int i = 1; i < lines.size() - 1; i++) {
    int separator = lines[i].find(": ");
    string key = lines[i].substr(0, separator);
    string value = lines[i].substr(separator + 2, string::npos);
    headers[key] = value;
  }
  return headers;
}