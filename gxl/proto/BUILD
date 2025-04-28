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
        "@protobuf//src/google/protobuf/io",
        "@protobuf//src/google/protobuf/io:tokenizer",
        "@re2",
    ],
)

cc_library(
    name = "parse_text_proto",
    hdrs = ["parse_text_proto.h"],
    deps = [
        "@abseil-cpp//absl/log:check",
        "@protobuf",
    ],
)

cc_library(
    name = "protobuf_util",
    hdrs = ["protobuf_util.h"],
    deps = [
        "@abseil-cpp//absl/log",
        "@protobuf",
    ],
)

cc_library(
    name = "protoutil",
    hdrs = ["protoutil.h"],
    deps = [
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/time",
        "@protobuf",
    ],
)

cc_library(
    name = "proto_enum_utils",
    hdrs = ["proto_enum_utils.h"],
    deps = [
        "@abseil-cpp//absl/types:span",
        "@protobuf",
    ],
)
