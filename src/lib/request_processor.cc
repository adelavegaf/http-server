#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "http_request.h"
#include "request_processor.h"

using std::string;
void RequestProcessor::Process(const char buffer[], int size) {
  for (int i = 0; i < size; i++) {
    cur_request += buffer[i];
  }

  int bytes_in_body = GetContentLength(cur_request);

  string header_end_key = "\r\n\r\n";
  auto header_end_pos = cur_request.find(header_end_key);

  if (header_end_pos == string::npos) {
    // We havent reached the end of the header -> keep on processing more bytes.
    std::cout << "Haven't reached the end of the header" << std::endl;
    return;
  }

  if (bytes_in_body <= 0) {
    // There's no body -> we finished processing this request.
    std::cout << "No body -> Finished processing request" << std::endl;
    HttpRequest req(cur_request);
    cur_request = "";
    return;
  }

  auto body_byte_count =
      cur_request.length() - (header_end_pos + header_end_key.length());

  if (body_byte_count < bytes_in_body) {
    // We are still missing more bytes of the body.
    std::cout << "Missing bytes on body" << std::endl;
    return;
  }

  std::cout << "Finished processing request + body" << std::endl;
  HttpRequest req(cur_request);
  cur_request = "";

  // TODO(adelavega): determine what to do with possible left over bytes that
  // dont belong to this request but the next one: body_byte_count >
  // bytes_in_body
}

int RequestProcessor::GetContentLength(string request) {
  string key = "Content-Length: ";
  auto key_pos = request.find(key);
  if (key_pos == string::npos) {
    return -1;
  }
  auto end_pos = request.find("\r\n", key_pos);
  auto start_pos = key_pos + key.length();
  string content_length_str = request.substr(start_pos, end_pos - start_pos);
  return std::stoi(content_length_str);
}
