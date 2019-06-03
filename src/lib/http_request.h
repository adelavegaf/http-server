#include <map>
#include <string>

using std::map;
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

class HttpRequest {
 private:
  // Header attributes

  // Request status line
  Method method;
  string uri;
  string version;

  // Optional
  map<string, string> optional_headers;
  Method StringToHttpMethod(string m);

 public:
  HttpRequest(string r);
  ~HttpRequest();
};
