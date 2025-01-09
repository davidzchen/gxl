licenses(["notice"])

# Requires --copt -funsigned-char when compiling (unsigned chars).

cc_library(
    name = "unicodetext",
    srcs = [
        "unicodetext.cc",
        "unilib.cc",
    ],
    hdrs = [
        "unicodetext.h",
        "unilib.h",
        "unilib_utf8_utils.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//gxl/base:types",
        "//third_party/utf",
        "@abseil-cpp//absl/base",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/strings:str_format",
    ],
)

cc_test(
    name = "unicodetext_test",
    srcs = [
        "unicodetext_test.cc",
    ],
    deps = [
        ":unicodetext",
        "//third_party/utf",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "unicodetext_main",
    srcs = ["unicodetext_main.cc"],
    deps = [":unicodetext"],
)
