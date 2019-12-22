#pragma once

#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <vector>
#include "files.h"
#include "period.h"
#include "command.h"
#include <ctime>

namespace filesys = boost::filesystem;
using namespace boost::program_options;

class HistoryExtension {
private:
    const std::string username = getenv("USER");

public:
    static void startListening(int, char**);

    static void getConsoleHistory(const Period&);

    //static void getActionsHistory(const Period&);

    static void getFilesystemHistory(const filesys::path&, const Period&);

    static void getCommand(options_description&, options_description&);

    static void notifyCommandError(const std::string&);

    static void notifyPathError(const std::string&);

    static void notifyPeriodError(const std::string&);

    static void getHelp(options_description& desc);

    static bool isValidPeriod(const Period&);
};
