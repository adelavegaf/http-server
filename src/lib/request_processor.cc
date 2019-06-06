#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "http_request.h"
#include "request_processor.h"

using std::optional;
using std::string;

optional<HttpRequest> RequestProcessor::Process(const char buffer[], int size) {
  for (int i = 0; i < size; i++) {
    cur_request += buffer[i];
  }

  string header_end_key = "\r\n\r\n";
  auto header_end_pos = cur_request.find(header_end_key);

  if (header_end_pos == string::npos) {
    // We havent reached the end of the header -> keep on processing more bytes.
    std::cout << "Haven't reached the end of the header" << std::endl;
    return std::nullopt;
  }

  string header = cur_request.substr(0, header_end_pos + header_end_key.length());
  auto bytes_in_body = GetContentLength(header);

  if (!bytes_in_body || *bytes_in_body <= 0) {
    std::cout << "No body -> Finished processing request" << std::endl;
    HttpRequest req(header);
    cur_request = cur_request.substr(header.length(), string::npos);
    return {req};
  }

  auto body_byte_count = cur_request.length() - header.length();

  if (body_byte_count < *bytes_in_body) {
    std::cout << "Missing bytes on body" << std::endl;
    return std::nullopt;
  } else if (body_byte_count == *bytes_in_body) {
    std::cout << "Finished processing request + body" << std::endl;
    HttpRequest req(cur_request);
    cur_request = "";
    return {req};
  } else {
    std::cout << "Finished processing request + body + extra" << std::endl;
    HttpRequest req(cur_request.substr(0, header.length() + *bytes_in_body));
    cur_request = cur_request.substr(header.length() + *bytes_in_body, string::npos);
    return {req};
  }
}

optional<unsigned long> RequestProcessor::GetContentLength(string header) {
  string key = "Content-Length: ";
  auto key_pos = header.find(key);
  if (key_pos == string::npos) {
    return std::nullopt;
  }
  auto end_pos = header.find("\r\n", key_pos);
  auto start_pos = key_pos + key.length();
  string content_length_str = header.substr(start_pos, end_pos - start_pos);
  return std::stoi(content_length_str);
}
