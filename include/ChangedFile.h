#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

class ChangedFile {
public:
    ChangedFile(const std::string& fileName,
                const bfs::path& path,
                const std::time_t& time);

    std::string getFileName();

    bfs::path   getPath();

    std::time_t getTime();

private:
    std::string fileName_;

    bfs::path   path_;

    std::time_t time_;
};
