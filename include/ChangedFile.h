#pragma once
#include <boost/filesystem.hpp>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

namespace bfs = boost::filesystem;

class ChangedFile {
 public:
  ChangedFile(const std::string& fileName, const bfs::path& path,
              const std::time_t& time);

  inline std::string getFileName() { return this->fileName_; }

  inline bfs::path getPath() { return this->path_; }

  inline std::time_t getTime() { return this->time_; }

 private:
  std::string fileName_;

  bfs::path path_;

  std::time_t time_;
};
