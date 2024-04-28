load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# From https://github.com/kythe/kythe/blob/d8b94df81eca2ec3b1430178dca95abe1423c18b/setup.bzl
def github_archive(name, repo_name, commit, kind = "zip", strip_prefix = "", **kwargs):
    """Defines a GitHub commit-based repository rule."""
    project = repo_name[repo_name.index("/"):]
    if "sha256" in kwargs:
        print("Ignoring unstable GitHub sha256 argument in", name)
        kwargs.pop("sha256")
    http_archive(
        name = name,
        strip_prefix = "{project}-{commit}/{prefix}".format(
            project = project,
            commit = commit,
            prefix = strip_prefix,
        ),
        urls = [u.format(commit = commit, repo_name = repo_name, kind = kind) for u in [
            "https://mirror.bazel.build/github.com/{repo_name}/archive/{commit}.{kind}",
            "https://github.com/{repo_name}/archive/{commit}.{kind}",
        ]],
        canonical_id = commit,
        **kwargs
    )
