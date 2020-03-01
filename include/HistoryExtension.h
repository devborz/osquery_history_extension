#pragma once
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "ChangedFile.h"
#include "ExecutedCommand.h"
#include "FilesLib.h"
#include "JsonSerializer.h"
#include "OptionsLib.h"
#include "VimLib.h"

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

class HistoryExtension {
 private:
  const std::string username = getenv("USER");

  static void getBashHistory();

  static void getFilesystemHistory();

  static void getVimHistory();

  static void iterate(bfs::path, std::vector<ChangedFile>& list);

  static void notify(const std::string&);

  static inline bfs::path getPath() {
    return bfs::path(std::string(getenv("HOME")));
  }

 public:
  static void work(int, char**);
};
