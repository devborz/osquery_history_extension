#pragma once
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "ChangedFile.h"
#include "ExecutedCommand.h"
#include "VimLib.h"

namespace bfs = boost::filesystem;

class JsonSerializer {
 public:
  static void saveBashHistory(std::vector<ExecutedCommand>&);

  static void saveFilesystemHistory(std::vector<ChangedFile>&);

  static void saveVimCommandsHistory(std::vector<VimCommand>&);

  static void saveVimFileMarksHistory(std::vector<VimFileMark>&);
};
