#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

class VimCommand {
public:
    VimCommand(const std::string&, const std::time_t);

    VimCommand(const VimCommand& command);

    VimCommand& operator=(const VimCommand& command);

    std::string  getCommand();

    std::time_t  getTime();

    static VimCommand parseCommand(const std::string&,
                                   const std::string&);

private:
    std::string command_;
    std::time_t time_;
};

class VimFileMark {
public:
    VimFileMark(const std::string&,
                const bfs::path&,
                const std::time_t&,
                const unsigned int&,
                const unsigned int&);

    VimFileMark(const VimFileMark& fileMark);

    VimFileMark& operator=(const VimFileMark& fileMark);

    static VimFileMark parseFileMark(const std::string&,
                                     const std::string&);
    std::string  getFileName();

    std::time_t  getTime();

    bfs::path    getPath();

    unsigned int getRow();

    unsigned int getColumn();

private:
    bfs::path path_;

    std::string filename_;

    std::time_t time_;

    unsigned int posRow_;

    unsigned int posCol_;
};
