#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <vector>
#include "files.h"
#include "period.h"
#include "command.h"
#include <ctime>

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

class HistoryExtension {
private:
    const std::string username = getenv("USER");

public:
    static void listen(int, char**);

    static void getConsoleHistory(const bfs::path&, const Period&);

    static void getFilesystemHistory(const bfs::path&, const Period&);

    static void getCommand(bpo::options_description&);

    static void notifyCommandError(const std::string&);

    static void notifyPathError(const std::string&);

    static void notifyPeriodError(const std::string&);

    static void getHelp(bpo::options_description& desc);

    static void checkBashConfig();

    static bool isValidPeriod(const Period&);
};
