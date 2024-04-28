load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

filegroup(
    name = "clang_tidy_config",
    srcs = [".clang-tidy"],
    visibility = ["//visibility:public"],
)

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {
        "//...": "",
    },
)
