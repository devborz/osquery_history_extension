#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

class ExecutedCommand {
public:
    ExecutedCommand(const std::string& command,
                    const bfs::path& path,
                    const std::time_t& time);

    std::string getCommand();

    bfs::path   getPath();

    std::time_t getTime();

private:
    std::string command_;

    bfs::path   path_;

    std::time_t time_;
};
