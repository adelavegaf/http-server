cc_library(
  name = "http_server",
  srcs = ["http_server.cc"],
  hdrs = ["http_server.h"],
  visibility = ["//visibility:public"],
  deps = [
    ":request_processor",
  ]
)

cc_library(
  name = "request_processor",
  srcs = ["request_processor.cc"],
  hdrs = ["request_processor.h"],
  deps = [
    ":http_request"
  ]
)

cc_library(
  name = "http_request",
  srcs = ["http_request.cc"],
  hdrs = ["http_request.h"]
)