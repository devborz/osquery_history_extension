#pragma once

#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
#include <ctime>
#include <map>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

class JsonSaver {
public:
    static void saveCommamdsHistory(const std::vector<std::pair<std::string,
                                    std::pair<bfs::path, std::time_t>>>&);

    static void saveFilesystemsHistory(const std::vector<std::pair<bfs::path,
                                        std::time_t>>&);
};
