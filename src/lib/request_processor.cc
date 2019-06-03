#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "http_request.h"
#include "request_processor.h"

using std::string;
void RequestProcessor::Process(const char buffer[], int size) {
  unsigned int start_pos = cur_request.length() < 2 ? cur_request.length()
                                                    : cur_request.length() - 2;

  for (int i = 0; i < size; i++) {
    cur_request += buffer[i];
  }

  if (cur_request.find("\r\n\r\n", start_pos) != string::npos) {
    std::cout << "end of header" << std::endl;
    HttpRequest req(cur_request);
    cur_request = "";
  }
}