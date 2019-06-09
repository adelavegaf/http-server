cc_library(
  name = "server",
  srcs = ["server.cc"],
  hdrs = ["server.h"],
  visibility = ["//visibility:public"],
  deps = [
    ":request_processor",
    ":request",
    ":response",
  ]
)

cc_library(
  name = "request_processor",
  srcs = ["request_processor.cc"],
  hdrs = ["request_processor.h"],
  deps = [
    ":request"
  ]
)

cc_library(
  name = "request",
  srcs = ["request.cc"],
  hdrs = ["request.h"],
  visibility = ["//visibility:public"],
  deps = [
    ":method"
  ]
)

cc_library(
  name = "response",
  srcs = ["response.cc"],
  hdrs = ["response.h"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "method",
  srcs = ["method.cc"],
  hdrs = ["method.h"]
)

cc_test(
    name = "test",
    srcs = ["request_processor_test.cc"],
    deps = [
        ":request_processor",
        ":request",
        ":method",
        "@gtest//:gtest",
    ],
)