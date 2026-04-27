load(
    "@abseil-cpp//absl:copts/configure_copts.bzl",
    "ABSL_DEFAULT_COPTS",
    "ABSL_DEFAULT_LINKOPTS",
    "ABSL_TEST_COPTS",
)
load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "types",
    hdrs = ["types.h"],
)

cc_library(
    name = "source_location",
    hdrs = ["source_location.h"],
)

cc_library(
    name = "endian",
    hdrs = [
        "endian.h",
        "internal/unaligned_access.h",
    ],
    copts = ABSL_DEFAULT_COPTS,
    linkopts = ABSL_DEFAULT_LINKOPTS,
    deps = [
        "@abseil-cpp//absl/base:base",
        "@abseil-cpp//absl/base:config",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/base:nullability",
    ],
)

cc_test(
    name = "endian_test",
    srcs = ["endian_test.cc"],
    copts = ABSL_TEST_COPTS,
    deps = [
        ":endian",
        "@abseil-cpp//absl/base:config",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
