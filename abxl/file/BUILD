package(default_visibility = ["//visibility:public"])

cc_library(
    name = "file_path",
    srcs = ["file_path.cc"],
    hdrs = ["file_path.h"],
    deps = [
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "file_helpers",
    srcs = ["file_helpers.cc"],
    hdrs = ["file_helpers.h"],
    deps = [
        ":file_path",
        "//abxl/status:status_builder",
        "//abxl/status:status_macros",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
)
