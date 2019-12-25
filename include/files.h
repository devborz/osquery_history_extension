#pragma once

#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

namespace fs = boost::filesystem;

class Files {
public:
    static void pushToList(const fs::path&,
                std::vector<std::pair<fs::path, std::time_t>>&);

    static void sortByTime(std::vector<std::pair<fs::path, std::time_t>>&);


    /*static void print(const std::vector<std::pair<fs::path, std::time_t>>&,
                      const fs::path&);*/

    //static fs::path getRealtivePath(const fs::path&, const fs::path&);
};
