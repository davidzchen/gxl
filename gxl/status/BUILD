package(default_visibility = ["//visibility:public"])

cc_library(
    name = "status_macros",
    hdrs = ["status_macros.h"],
    deps = [
        ":status_builder",
        "//gxl/base:source_location",
        "@abseil-cpp//absl/status",
    ],
)

cc_library(
    name = "status_builder",
    srcs = ["status_builder.cc"],
    hdrs = ["status_builder.h"],
    deps = [
        "//gxl/base:source_location",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/memory",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings",
    ],
)

cc_test(
    name = "status_builder_test",
    size = "small",
    srcs = ["status_builder_test.cc"],
    deps = [
        ":status_builder",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
