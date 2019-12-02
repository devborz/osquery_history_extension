#pragma once

#include <boost/filesystem.hpp>
#include "period.h"
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

namespace fs = boost::filesystem;

class Files {
public:
    static bool checkIsRecentlyChanged(const fs::path& pathToObj,
                const Period& period);

    static void pushToList(const fs::path& pathToObj,
                std::vector<std::pair<fs::path, std::time_t>>&
                recentlyChangedFiles);

    static void sortByTime(std::vector<std::pair<fs::path, std::time_t>>&
                recentlyChangedFiles);

    static void print(std::vector<std::pair<fs::path, std::time_t>>&
                recentlyChangedFiles);
};
