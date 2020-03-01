#pragma once
#include <boost/filesystem.hpp>
#include <chrono>
#include <iostream>
#include <string>

namespace bfs = boost::filesystem;

class VimCommand {
 public:
  VimCommand(const std::string&, const std::time_t);

  VimCommand(const VimCommand& command);

  VimCommand& operator=(const VimCommand& command);

  inline std::string getCommand() { return this->command_; }

  inline std::time_t getTime() { return this->time_; }

  static VimCommand parseCommand(const std::string&, const std::string&);

 private:
  std::string command_;

  std::time_t time_;
};

class VimFileMark {
 public:
  VimFileMark(const std::string&, const bfs::path&, const std::time_t&,
              const unsigned int&, const unsigned int&);

  VimFileMark(const VimFileMark& fileMark);

  VimFileMark& operator=(const VimFileMark& fileMark);

  static VimFileMark parseFileMark(const std::string&, const std::string&);

  inline std::string getFileName() { return this->filename_; }

  inline std::time_t getTime() { return this->time_; }

  inline bfs::path getPath() { return this->path_; }

  inline unsigned int getRow() { return this->posRow_; }

  inline unsigned int getColumn() { return this->posCol_; }

 private:
  bfs::path path_;

  std::string filename_;

  std::time_t time_;

  unsigned int posRow_;

  unsigned int posCol_;
};
