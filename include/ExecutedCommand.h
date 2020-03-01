#pragma once
#include <boost/filesystem.hpp>
#include <chrono>
#include <iostream>
#include <string>

namespace bfs = boost::filesystem;

class ExecutedCommand {
 public:
  ExecutedCommand(const std::string& command, const bfs::path& path,
                  const std::time_t& time);

  inline std::string getCommand() { return this->command_; }

  inline bfs::path getPath() { return this->path_; }

  inline std::time_t getTime() { return this->time_; }

  static bool parseEvent(std::string&, std::string&, bfs::path&, std::time_t&);

 private:
  static bool isTime(const std::string& time);

  static unsigned int findSpace(const std::string&);

  static unsigned int findSpace(const std::string&, const unsigned int&);

  std::string command_;

  bfs::path path_;

  std::time_t time_;
};
