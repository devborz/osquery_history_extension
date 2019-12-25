#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <vector>
#include <ctime>
#include "files.h"
#include "command.h"
#include "JsonSaver.h"

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

class HistoryExtension {
private:
    const std::string username = getenv("USER");


    static void getCommandlineHistory(const bfs::path&);


    static void getFilesystemHistory(const bfs::path&);


    static void iterate(bfs::path,
                        std::vector<std::pair<bfs::path, std::time_t>>& list);

    static void getCommand(bpo::options_description&);


    static void notifyCommandError(const std::string&);


    static void notify(const std::string&);


    static void getHelp(bpo::options_description& desc);


    //static void checkBashConfig();


    static Command readCommand(const bpo::variables_map&, unsigned int&);


    static bfs::path getPath(const bpo::variables_map&);

public:
    static void work(int, char**);
};
