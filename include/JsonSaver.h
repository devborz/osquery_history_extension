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

namespace bfs = boost::filesystem;

class JsonSaver {
public:
    static void saveCommandsHistory(std::vector<ExecutedCommand>&);

    static void saveFilesystemsHistory(std::vector<ChangedFile>&);
};
