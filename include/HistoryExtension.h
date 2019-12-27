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
#include "ChangedFile.h"
#include "ExecutedCommand.h"
#include "FilesLib.h"
#include "CommandsLib.h"
#include "JsonSaver.h"

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

class HistoryExtension {
private:
    const std::string username = getenv("USER");


    static void getBashHistory(const bfs::path&);


    static void getFilesystemHistory(const bfs::path&);


    static void iterate(bfs::path, std::vector<ChangedFile>& list);

    static void getCommand(bpo::options_description&);


    static void notifyCommandError(const std::string&);


    static void notify(const std::string&);


    static void getHelp(bpo::options_description& desc);


    static Command readCommand(const bpo::variables_map&, unsigned int&);


    static bfs::path getPath(const bpo::variables_map&);

public:
    static void work(int, char**);
};
