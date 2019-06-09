#ifndef HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_
#define HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_

#include <string>

namespace http {

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

Method StringToHttpMethod(std::string m);
std::string HttpMethodToString(Method m);

}  // namespace http

#endif  // HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_