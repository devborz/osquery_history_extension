#pragma once
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <boost/filesystem.hpp>
#include "ChangedFile.h"
#include "ExecutedCommand.h"
#include "VimSession.h"

namespace bfs = boost::filesystem;

class JsonSaver {
public:
    static void saveBashHistory(std::vector<ExecutedCommand>&);

    static void saveFilesystemHistory(std::vector<ChangedFile>&);

    static void saveVimHistory(std::vector<VimSession>&);
};
