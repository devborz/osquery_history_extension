#pragma once

#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

class JsonSaver {
public:
    static void saveCommamdsHistory(const std::vector<std::pair<std::string,
                                    std::pair<bfs::path, std::time_t>>>&);

    static void saveFilesystemsHistory(const std::vector<std::pair<bfs::path,
                                        std::time_t>>&);
};
