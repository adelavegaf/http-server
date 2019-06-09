#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "request.h"
#include "request_processor.h"

namespace http {

RequestProcessor::RequestProcessor() { cur_request = ""; }

std::optional<Request> RequestProcessor::Process(const char buffer[],
                                                 const int size) {
  for (int i = 0; i < size; i++) {
    cur_request += buffer[i];
  }

  std::string header_end_key = "\r\n\r\n";
  auto header_end_pos = cur_request.find(header_end_key);

  if (header_end_pos == std::string::npos) {
    // We have not reached the end of the header marked by two consecutive \r\n.
    return std::nullopt;
  }

  // header will include \r\n\r\n
  std::string header =
      cur_request.substr(0, header_end_pos + header_end_key.length());

  auto body_byte_count = cur_request.length() - header.length();
  auto bytes_in_body = GetContentLength(header);

  if (body_byte_count < bytes_in_body) {
    // We are missing some bytes from the request's body.
    return std::nullopt;
  }

  std::string body = cur_request.substr(header.length(), bytes_in_body);
  cur_request =
      cur_request.substr(header.length() + bytes_in_body, std::string::npos);

  Request req = ParseRequest(header, body);
  return {req};
}

unsigned long RequestProcessor::GetContentLength(const std::string header) {
  std::string key = "Content-Length: ";
  auto key_pos = header.find(key);
  if (key_pos == std::string::npos) {
    return 0;
  }
  auto end_pos = header.find("\r\n", key_pos);
  auto start_pos = key_pos + key.length();
  std::string content_length_str =
      header.substr(start_pos, end_pos - start_pos);
  return std::stoul(content_length_str);
}

Request RequestProcessor::ParseRequest(const std::string header,
                                       const std::string body) {
  size_t start_pos = 0;
  std::vector<std::string> lines;
  std::string delimiter = "\r\n";

  while (true) {
    size_t pos = header.find(delimiter, start_pos);
    if (pos == std::string::npos || start_pos == pos) {
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

RequestStatusLine RequestProcessor::ParseStatusLine(const std::string s) {
  size_t start_pos = 0;
  size_t next_pos = s.find(" ", start_pos);
  std::string m = s.substr(start_pos, next_pos);
  Method method = StringToMethod(m);

  start_pos = next_pos + 1;
  next_pos = s.find(" ", start_pos);
  std::string url = s.substr(start_pos, next_pos - start_pos);

  std::string protocol = s.substr(next_pos + 1, std::string::npos);

  return {method, url, protocol};
}

std::map<std::string, std::string> RequestProcessor::ParseHeaders(
    const std::vector<std::string> lines) {
  std::map<std::string, std::string> headers;
  for (int i = 1; i < lines.size() - 1; i++) {
    int separator = lines[i].find(": ");
    std::string key = lines[i].substr(0, separator);
    std::string value = lines[i].substr(separator + 2, std::string::npos);
    headers[key] = value;
  }
  return headers;
}

}  // namespace http