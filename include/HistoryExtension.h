#pragma once

#include <fstream>
#include <chrono>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <vector>
#include "files.h"
#include "period.h"
#include "command.h"
#include <ctime>

namespace filesys = boost::filesystem;

class HistoryExtension {
private:
    const std::string username = getenv("USER");

public:
    static void startListening();

    static void getConsoleHistory(const Period& period);

    static void getActionsHistory(const Period& period);

    static void getFilesystemHistory(const filesys::path& pathToDir,
                                     const Period& period);
};
