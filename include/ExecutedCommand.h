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

    static bool parseEvent(std::string&, std::string&,
                           bfs::path&, std::time_t&);

private:
    static bool isTime(const std::string& time);

    static unsigned int findSpace(const std::string&);

    static unsigned int findSpace(const std::string&, const unsigned int&);

    std::string command_;

    bfs::path   path_;

    std::time_t time_;
};
