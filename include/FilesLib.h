#pragma once

#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include "ChangedFile.h"

namespace fs = boost::filesystem;

class Files {
public:
    static void pushToList(const fs::path&, std::vector<ChangedFile>&);

    static void sortByTime(std::vector<ChangedFile>&);
};
