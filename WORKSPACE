load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("//tools:repository.bzl", "github_archive")

# Skylib

http_archive(
    name = "bazel_skylib",
    sha256 = "66ffd9315665bfaafc96b52278f57c7e2dd09f5ede279ea6d39b2be471e7e3aa",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

# C++

http_archive(
    name = "rules_cc",
    sha256 = "2037875b9a4456dce4a79d112a8ae885bbc4aad968e6587dca6e64f3a0900cdf",
    strip_prefix = "rules_cc-0.0.9",
    urls = ["https://github.com/bazelbuild/rules_cc/releases/download/0.0.9/rules_cc-0.0.9.tar.gz"],
)

http_archive(
    name = "com_google_absl",
    sha256 = "e639cb99f35c8754dab55ce9408b6a98457c8880b0fd1cb8926cd104a08517ce",
    strip_prefix = "abseil-cpp-ad5499a290fd98de54ee54dcf8120f8d287640ce",
    urls = ["https://github.com/abseil/abseil-cpp/archive/ad5499a290fd98de54ee54dcf8120f8d287640ce.zip"],
)

# Protocol Buffers

http_archive(
    name = "rules_proto",
    sha256 = "dc3fb206a2cb3441b485eb1e423165b231235a1ea9b031b4433cf7bc1fa460dd",
    strip_prefix = "rules_proto-5.3.0-21.7",
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/5.3.0-21.7.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

# Testing

http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-71140c3ca7a87bb1b5b9c9f1500fea8858cce344",
    urls = ["https://github.com/google/googletest/archive/71140c3ca7a87bb1b5b9c9f1500fea8858cce344.zip"],
)

http_archive(
    name = "com_github_google_benchmark",
    strip_prefix = "benchmark-62edc4fb00e1aeab86cc69c70eafffb17219d047",
    urls = ["https://github.com/google/benchmark/archive/62edc4fb00e1aeab86cc69c70eafffb17219d047.zip"],
)

# clang-tidy

git_repository(
    name = "bazel_clang_tidy",
    commit = "43bef6852a433f3b2a6b001daecc8bc91d791b92",
    remote = "https://github.com/erenon/bazel_clang_tidy.git",
)

github_archive(
    name = "toolchains_llvm",
    commit = "c5f221a3bdb7bcca9a3079eb032c9fa7333f52cc",
    repo_name = "bazel-contrib/toolchains_llvm",
)

load("@toolchains_llvm//toolchain:deps.bzl", "bazel_toolchain_dependencies")

bazel_toolchain_dependencies()

load("@toolchains_llvm//toolchain:rules.bzl", "llvm_toolchain")

llvm_toolchain(
    name = "llvm_toolchain",
    llvm_versions = {
        "": "15.0.6",
        "darwin-aarch64": "15.0.7",
        "darwin-x86_64": "15.0.7",
    },
)

load("@llvm_toolchain//:toolchains.bzl", "llvm_register_toolchains")

llvm_register_toolchains()

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    strip_prefix = "bazel-compile-commands-extractor-5bcb0bd8a917b2b48fb5dc55818515f4be3b63ff",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/5bcb0bd8a917b2b48fb5dc55818515f4be3b63ff.tar.gz",
)

load(
    "@hedron_compile_commands//:workspace_setup.bzl",
    "hedron_compile_commands_setup",
)

hedron_compile_commands_setup()

load(
    "@hedron_compile_commands//:workspace_setup_transitive.bzl",
    "hedron_compile_commands_setup_transitive",
)

hedron_compile_commands_setup_transitive()

load(
    "@hedron_compile_commands//:workspace_setup_transitive_transitive.bzl",
    "hedron_compile_commands_setup_transitive_transitive",
)

hedron_compile_commands_setup_transitive_transitive()

load(
    "@hedron_compile_commands//:workspace_setup_transitive_transitive_transitive.bzl",
    "hedron_compile_commands_setup_transitive_transitive_transitive",
)

hedron_compile_commands_setup_transitive_transitive_transitive()
