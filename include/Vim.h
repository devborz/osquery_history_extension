#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

class VimCommand {
public:
    VimCommand(const std::string&, const std::time_t);

    static VimCommand parseCommand(
                        const std::string&,
                        const std::string&
                      );

private:
    std::string command_;
    std::time_t time_;
};

class VimFileMark {
public:
    VimFileMark(
                const std::string&,
                const bfs::path&,
                const std::time_t&,
                const unsigned int&,
                const unsigned int&
                );


    static VimFileMark parseFileMark(
                        const std::string&,
                        const std::string&
                      );

private:
    bfs::path path_;

    std::string filename_;

    std::time_t time_;

    unsigned int posRow_;

    unsigned int posCol_;
};
