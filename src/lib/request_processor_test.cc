#include <iostream>
#include <optional>
#include <string>
#include "gtest/gtest.h"

#include "http_method.h"
#include "http_request.h"
#include "request_processor.h"

string getRequest(string method, string body) {
  // clang-format off
  string request = method +
      " / HTTP/1.1\r\n"
      "Host: localhost:8080\r\n"
      "Connection: keep-alive\r\n"
      "Upgrade-Insecure-Requests: 1\r\n"
      "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36\r\n"
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n"
      "Purpose: prefetch\r\n"
      "Accept-Encoding: gzip, deflate, br\r\n"
      "Accept-Language: es-ES,es;q=0.9,en;q=0.8\r\n";
  // clang-format on

  if (body.length() > 0) {
    request += "Content-Length: " + std::to_string(body.length()) + "\r\n";
  }

  request += "\r\n";
  request += body;

  return request;
}

TEST(RequestProcessorTest, ParsesGetRequestCorrectly) {
  string request = getRequest("GET", "");
  char buffer[request.length()];
  for (int i = 0; i < request.length(); i++) {
    buffer[i] = request[i];
  }
  RequestProcessor rp;
  std::optional<HttpRequest> req = rp.Process(buffer, request.length());
  ASSERT_TRUE(req) << "A request should have been returned";
  ASSERT_EQ(req->GetMethod(), Method::GET);
  ASSERT_EQ(req->GetBody(), "");
}

TEST(RequestProcessorTest, ParsesPostRequestCorrectly) {
  string body = "body";
  string request = getRequest("POST", body);
  char buffer[request.length()];
  for (int i = 0; i < request.length(); i++) {
    buffer[i] = request[i];
  }
  RequestProcessor rp;
  std::optional<HttpRequest> req = rp.Process(buffer, request.length());
  ASSERT_TRUE(req) << "A request should have been returned";
  ASSERT_EQ(req->GetMethod(), Method::POST);
  ASSERT_EQ(req->GetBody(), body);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}