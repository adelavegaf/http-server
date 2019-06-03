#ifndef HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_
#define HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_

#include <string>

enum class Method {
  OPTIONS,
  GET,
  HEAD,
  POST,
  PUT,
  DELETE,
  TRACE,
  CONNECT,
  UNKNOWN
};

inline Method stringToHttpMethod(std::string m) {
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
#endif  // HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_