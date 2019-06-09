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

TEST(RequestProcessorTest, ParsesGetRequest) {
  string request = getRequest("GET", "");
  char buffer[request.length()];
  for (int i = 0; i < request.length(); i++) {
    buffer[i] = request[i];
  }
  RequestProcessor rp;
  std::optional<HttpRequest> req = rp.Process(buffer, request.length());
  ASSERT_TRUE(req) << "A request should have been returned";
  ASSERT_EQ(req->method, http_method::Method::GET);
  ASSERT_EQ(req->body, "");
}

TEST(RequestProcessorTest, ParsesPostRequest) {
  string body = "body";
  string request = getRequest("POST", body);
  char buffer[request.length()];
  for (int i = 0; i < request.length(); i++) {
    buffer[i] = request[i];
  }
  RequestProcessor rp;
  std::optional<HttpRequest> req = rp.Process(buffer, request.length());
  ASSERT_TRUE(req) << "A request should have been returned";
  ASSERT_EQ(req->method, http_method::Method::POST);
  ASSERT_EQ(req->body, body);
}

TEST(RequestProcessorTest, ParsesMangledRequests) {
  string body1 = "";
  string req1 = getRequest("GET", body1);
  string body2 = "test body";
  string req2 = getRequest("POST", body2);
  string body3 = "body test";
  string req3 = getRequest("POST", body3);

  char buffer[req1.length() + req2.length()];
  int buffer_index = 0;
  for (int i = 0; i < req1.length(); i++) {
    buffer[buffer_index++] = req1[i];
  }
  int req2_missing_bytes = 100;
  for (int i = 0; i < req2.length() - req2_missing_bytes; i++) {
    buffer[buffer_index++] = req2[i];
  }
  RequestProcessor rp;
  std::optional<HttpRequest> req;

  req = rp.Process(buffer, buffer_index);
  ASSERT_TRUE(req) << "A request should have been returned";
  ASSERT_EQ(req->method, http_method::Method::GET);
  ASSERT_EQ(req->body, body1);

  buffer_index = 0;

  for (int i = 0; i < req2_missing_bytes; i++) {
    buffer[buffer_index++] = req2[req2.length() - req2_missing_bytes + i];
  }
  int req3_missing_bytes = 33;
  for (int i = 0; i < req3.length() - req3_missing_bytes; i++) {
    buffer[buffer_index++] = req3[i];
  }

  req = rp.Process(buffer, buffer_index);
  ASSERT_TRUE(req) << "A request should have been returned";
  ASSERT_EQ(req->method, http_method::Method::POST);
  ASSERT_EQ(req->body, body2);

  buffer_index = 0;

  for (int i = 0; i < req3_missing_bytes; i++) {
    buffer[buffer_index++] = req3[req3.length() - req3_missing_bytes + i];
  }

  req = rp.Process(buffer, buffer_index);
  ASSERT_TRUE(req) << "A request should have been returned";
  ASSERT_EQ(req->method, http_method::Method::POST);
  ASSERT_EQ(req->body, body3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}