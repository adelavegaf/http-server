#include <string>

#include "http_method.h"

namespace http {

Method StringToHttpMethod(std::string m) {
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

std::string HttpMethodToString(Method m) {
  if (m == Method::GET) {
    return "GET";
  } else if (m == Method::POST) {
    return "POST";
  } else if (m == Method::PUT) {
    return "PUT";
  } else if (m == Method::DELETE) {
    return "DELETE";
  } else if (m == Method::OPTIONS) {
    return "OPTIONS";
  } else if (m == Method::HEAD) {
    return "HEAD";
  } else if (m == Method::CONNECT) {
    return "CONNECT";
  } else if (m == Method::TRACE) {
    return "TRACE";
  } else {
    return "";
  }
}

}  // namespace http