package(default_visibility = ["//visibility:public"])

cc_library(
    name = "path",
    srcs = ["path.cc"],
    hdrs = ["path.h"],
    deps = [
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "filesystem",
    srcs = ["filesystem.cc"],
    hdrs = ["filesystem.h"],
    deps = [
        ":path",
        "//abxl/status:status_builder",
        "//abxl/status:status_macros",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings",
    ],
)
