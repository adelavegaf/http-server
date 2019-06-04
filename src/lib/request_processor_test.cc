#include <iostream>
#include <optional>
#include "gtest/gtest.h"

#include "http_method.h"
#include "http_request.h"
#include "request_processor.h"

TEST(RequestProcessorTest, ParsesEmptyBodyRequestCorrectly) {
  // clang-format off
  string header =
      "GET / HTTP/1.1\r\n"
      "Host: localhost:8080\r\n"
      "Connection: keep-alive\r\n"
      "Upgrade-Insecure-Requests: 1\r\n"
      "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36\r\n"
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n"
      "Purpose: prefetch\r\n"
      "Accept-Encoding: gzip, deflate, br\r\n"
      "Accept-Language: es-ES,es;q=0.9,en;q=0.8\r\n"
      "\r\n";
  // clang-format on
  char buffer[header.length()];
  for (int i = 0; i < header.length(); i++) {
    buffer[i] = header[i];
  }
  RequestProcessor rp;
  std::optional<HttpRequest> req = rp.Process(buffer, header.length());
  ASSERT_TRUE(req);
  auto req_method = req->GetMethod();
  ASSERT_EQ(req_method, Method::GET);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}