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
#include "ChangedFile.h"
#include "ExecutedCommand.h"
#include "VimLib.h"
#include "FilesLib.h"
#include "OptionsLib.h"
#include "JsonSaver.h"

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

class HistoryExtension {
private:
    const std::string username = getenv("USER");


    static void getBashHistory();


    static void getFilesystemHistory();


    static void getVimHistory();


    static void iterate(bfs::path, std::vector<ChangedFile>& list);


    static void notify(const std::string&);


    static bfs::path getPath();

public:
    static void work(int, char**);
};
