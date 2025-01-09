package(default_visibility = ["//visibility:public"])

cc_library(
    name = "protobuf_matchers",
    testonly = 1,
    srcs = ["protobuf_matchers.cc"],
    hdrs = ["protobuf_matchers.h"],
    deps = [
        "@abseil-cpp//absl/log:absl_check",
        "@abseil-cpp//absl/log:absl_log",
        "@abseil-cpp//absl/strings",
        "@googletest//:gtest",
        "@protobuf",
        "@protobuf//:differencer",
        "@protobuf//src/google/protobuf/io:tokenizer",
        "@re2",
    ],
)
