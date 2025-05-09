// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "gxl/file/filesystem.h"

#include "absl/strings/str_cat.h"

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>

#include <codecvt>
#include <locale>
#else
#include <dirent.h>
#endif  // _WIN32
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <cerrno>
#include <string>

#include "absl/status/status.h"
#include "gxl/file/file.h"
#include "gxl/file/path.h"
#include "gxl/status/status_builder.h"
#include "gxl/status/status_macros.h"

namespace gxl {
namespace {

// Helper class that returns all entries (files, directories) in a directory,
// except "." and "..". Example usage:
//
// DirectoryListing listing("/tmp");
// while (listing.HasNextEntry()) {
//   std::cout << listing.NextEntry() << std::endl;
// }
#ifndef _WIN32
class DirectoryListing {
 public:
  explicit DirectoryListing(const std::string& directory) {
    dir_ = opendir(directory.c_str());
    if (dir_) {
      ReadNextEntry();
    }
  }
  ~DirectoryListing() {
    if (dir_) {
      closedir(dir_);
    }
  }

  // Returns true if another entry in this directory listing is available.
  bool HasNextEntry() { return dir_ != nullptr && next_entry_ != nullptr; }

  // Returns the next entry in this directory listing and advances to the entry
  // after the one that is returned, if it exists.
  std::string NextEntry() {
    if (HasNextEntry()) {
      std::string result = std::string(next_entry_->d_name);
      ReadNextEntry();
      return result;
    } else {
      return std::string();
    }
  }

 private:
  void ReadNextEntry() {
    next_entry_ = readdir(dir_);
    while (next_entry_ && (std::string(next_entry_->d_name) == "." ||
                           std::string(next_entry_->d_name) == "..")) {
      next_entry_ = readdir(dir_);
    }
  }

  DIR* dir_ = nullptr;
  struct dirent* next_entry_ = nullptr;
};
#else
#if defined(UNICODE)
using PathString = std::wstring;

PathString Utf8ToNative(const std::string& string) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
  return converter.from_bytes(string.data(), string.data() + string.size());
}
std::string NativeToUtf8(const PathString& string) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
  return converter.to_bytes(string.data(), string.data() + string.size());
}
#define FILE_PATH_LITERAL_INTERNAL(x) L##x
#define FILE_PATH_LITERAL(x) FILE_PATH_LITERAL_INTERNAL(x)
#else
using PathString = std::string;
PathString Utf8ToNative(const std::string& string) { return string; }
std::string NativeToUtf8(const PathString& string) { return string; }
#define FILE_PATH_LITERAL(x) x
#endif

class DirectoryListing {
 public:
  explicit DirectoryListing(const std::string& directory)
      : directory_(Utf8ToNative(directory)) {
    PathString search_string = directory_ + Utf8ToNative("\\*.*");
    find_handle_ = FindFirstFile(search_string.c_str(), &find_data_);
  }

  ~DirectoryListing() {
    if (find_handle_ != INVALID_HANDLE_VALUE) {
      FindClose(find_handle_);
    }
  }

  // Returns true if another entry in this directory listing is available.
  bool HasNextEntry() { return find_handle_ != INVALID_HANDLE_VALUE; }

  // Returns the next entry in this directory listing and advances to the entry
  // after the one that is returned, if it exists.
  std::string NextEntry() {
    if (HasNextEntry()) {
      PathString result =
          directory_ + Utf8ToNative("\\") + PathString(find_data_.cFileName);
      ReadNextEntry();
      return NativeToUtf8(result);
    } else {
      return std::string();
    }
  }

 private:
  void ReadNextEntry() {
    int find_result = FindNextFile(find_handle_, &find_data_);
    while (find_result != 0 &&
           (PathString(find_data_.cFileName) == FILE_PATH_LITERAL(".") ||
            PathString(find_data_.cFileName) == FILE_PATH_LITERAL(".."))) {
      find_result = FindNextFile(find_handle_, &find_data_);
    }

    if (find_result == 0) {
      FindClose(find_handle_);
      find_handle_ = INVALID_HANDLE_VALUE;
    }
  }

  const PathString directory_;
  HANDLE find_handle_ = INVALID_HANDLE_VALUE;
  WIN32_FIND_DATA find_data_;
};
#endif  // _WIN32

}  // namespace

absl::Status AppendStringToFile(absl::string_view file_name,
                                absl::string_view contents) {
  FILE* fp = fopen(file_name.data(), "ab");
  if (!fp) {
    return gxl::InvalidArgumentErrorBuilder(GXL_LOC)
           << "Can't open file: " << file_name;
  }

  fwrite(contents.data(), sizeof(char), contents.size(), fp);
  size_t write_error = ferror(fp);
  if (fclose(fp) != 0 || write_error) {
    return gxl::InternalErrorBuilder(GXL_LOC)
           << "Error while writing file: " << file_name
           << ". Error message: " << strerror(write_error);
  }
  return absl::OkStatus();
}

absl::Status MatchInTopSubdirectories(const std::string& parent_directory,
                                      const std::string& file_name,
                                      std::vector<std::string>* results) {
  DirectoryListing parent_listing(parent_directory);

  while (parent_listing.HasNextEntry()) {
    std::string subdirectory =
        JoinPath(parent_directory, parent_listing.NextEntry());
    DirectoryListing subdirectory_listing(subdirectory);
    while (subdirectory_listing.HasNextEntry()) {
      std::string next_entry = subdirectory_listing.NextEntry();
      if (absl::EndsWith(next_entry, file_name)) {
        results->push_back(JoinPath(subdirectory, next_entry));
      }
    }
  }
  return absl::OkStatus();
}

absl::Status MatchFileTypeInDirectory(const std::string& directory,
                                      const std::string& file_suffix,
                                      std::vector<std::string>* results) {
  DirectoryListing directory_listing(directory);

  while (directory_listing.HasNextEntry()) {
    std::string next_entry = directory_listing.NextEntry();
    if (absl::EndsWith(next_entry, file_suffix)) {
      results->push_back(JoinPath(directory, next_entry));
    }
  }

  return absl::OkStatus();
}

absl::Status IsDirectory(absl::string_view file_name) {
  struct stat buffer;
  int status;
  status = stat(std::string(file_name).c_str(), &buffer);
  if (status == 0) {
    if ((buffer.st_mode & S_IFMT) == S_IFDIR) {
      return absl::OkStatus();
    }
    return absl::FailedPreconditionError("The path is not a directory.");
  }
  switch (errno) {
    case EACCES:
      return absl::PermissionDeniedError("Insufficient permissions.");
    default:
      return absl::NotFoundError("The path does not exist.");
  }
}

#ifndef _WIN32
int mkdir(std::string path) {
  return ::mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
}
#else
int mkdir(std::string path) { return _mkdir(path.c_str()); }
#endif

absl::Status RecursivelyCreateDir(absl::string_view path) {
  if (path.empty() || Exists(path, file::Defaults()).ok()) {
    return absl::OkStatus();
  }
  auto split_path = SplitPath(path);
  RETURN_IF_ERROR(RecursivelyCreateDir(split_path.first));
  if (mkdir(std::string(path)) != 0) {
    switch (errno) {
      case EACCES:
        return absl::PermissionDeniedError("Insufficient permissions.");
      default:
        return absl::UnavailableError("Failed to create directory.");
    }
  }
  return absl::OkStatus();
}

}  // namespace gxl
