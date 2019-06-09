#ifndef HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_
#define HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_

#include <string>

using std::string;

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

Method StringToHttpMethod(string m);
string HttpMethodToString(Method m);

#endif  // HTTP_SERVER_SRC_LIB_HTTP_METHOD_H_