#include <string>
#include <vector>

using std::string;
using std::vector;

class RequestProcessor {
 public:
  void Process(const char buffer[], int size);

 private:
  string cur_request;
};