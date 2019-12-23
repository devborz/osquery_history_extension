#pragma once

#include <iostream>
#include <boost/filesystem.hpp>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>
#include <ctime>
#include <map>

namespace fs = boost::filesystem;

enum Command {
    filesystem,
    commandline,
    help
};

class Commands {
public:
    static Command parse(const std::string& command);

    static void parseEvent(std::string&, std::string&, fs::path&, std::time_t&);

    static void print(const std::vector<std::pair<std::string,
                      std::pair<fs::path, std::time_t>>>&,
                      const fs::path&);

    static fs::path getRealtivePath(const fs::path&, const fs::path&);

    static bool isChildPath(const fs::path&, const fs::path&);
};
