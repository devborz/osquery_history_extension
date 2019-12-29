#include "VimLib.h"

VimCommand::VimCommand(const std::string& command, const std::time_t time) {

    this->command_ = command;

    this->time_    = time;
}

VimCommand::VimCommand(const VimCommand& vCommand) {

    this->command_ = vCommand.command_;

    this->time_    = vCommand.time_;
}

VimCommand VimCommand::parseCommand(const std::string& command,
                                    const std::string& info) {
    char comma = ',';
    unsigned int numberOfCommas = 0;

    unsigned int time_first_i = 0;
    unsigned int time_last_i  = 0;

    for (unsigned int  i = 0; i < info.length(); i++) {

        if (info[i] == comma) {
           numberOfCommas++;

           if (numberOfCommas == 2) {
               time_first_i = i;
           }
           else if (numberOfCommas == 3) {
               time_last_i = i;
           }
        }
    }

    std::string command_ = command.substr(1, command.length() - 1);

    std::string time_s = info.substr(time_first_i + 1,
                                     time_last_i - time_first_i - 1);
    std::time_t time_ = std::stoi(time_s);

    return VimCommand(command_, time_);
}

VimCommand& VimCommand::operator=(const VimCommand& command) {
    this->command_ = command.command_;

    this->time_ = command.time_;

    return *this;
}

std::string  VimCommand::getCommand() {
    return this->command_;
}

std::time_t  VimCommand::getTime() {
    return this->time_;
}

VimFileMark::VimFileMark(const std::string& filename,
                         const bfs::path& path,
                         const std::time_t& time,
                         const unsigned int& posRow,
                         const unsigned int& posCol) {

    this->filename_ = filename;

    this->path_     = path;

    this->time_     = time;

    this->posRow_   = posRow;

    this->posCol_   = posCol;
}

VimFileMark::VimFileMark(const VimFileMark& fileMark) {

    this->filename_ = fileMark.filename_;

    this->path_     = fileMark.path_;

    this->time_     = fileMark.time_;

    this->posRow_   = fileMark.posRow_;

    this->posCol_   = fileMark.posCol_;
}

VimFileMark& VimFileMark::operator=(const VimFileMark& fileMark) {

    this->filename_ = fileMark.filename_;

    this->path_     = fileMark.path_;

    this->time_     = fileMark.time_;

    this->posRow_   = fileMark.posRow_;

    this->posCol_   = fileMark.posCol_;

    return *this;
}

VimFileMark VimFileMark::parseFileMark(const std::string& line1,
                                       const std::string& line2) {

    char comma = ',';
    char quote = '\"';

    unsigned int numberOfCommas = 0;
    unsigned int numberOfQuotes = 0;

    unsigned int time_first_i = 0;
    unsigned int time_last_i  = 0;

    unsigned int path_first_i = 0;
    unsigned int path_last_i  = 0;

    unsigned int row_first_i = 0;
    unsigned int row_last_i  = 0;

    unsigned int col_first_i = 0;
    unsigned int col_last_i  = 0;

    for (unsigned int  i = 0; i < line2.length(); i++) {

        if (line2[i] == comma) {
           numberOfCommas++;

           if (numberOfCommas == 2) {
               row_first_i = i;
           }
           else if (numberOfCommas == 3) {
               row_last_i = i;
               col_first_i = i;
           }
           else if (numberOfCommas == 4) {
               col_last_i = i;
               time_first_i = i;
           }
           else if (numberOfCommas == 5) {
               time_last_i = i;
           }
        }
        else if (line2[i] == quote) {
           numberOfQuotes++;

           if (numberOfQuotes == 1) {
               path_first_i = i;
           }
           else if (numberOfQuotes == 2) {
               path_last_i = i;
           }
        }
    }

    std::string time_s = line2.substr(time_first_i + 1,
                                      time_last_i - time_first_i - 1);

    std::string path_s = line2.substr(path_first_i + 1,
                                      path_last_i - path_first_i - 1);

    std::string row_s = line2.substr(row_first_i + 1,
                                     row_last_i - row_first_i - 1);

    std::string col_s = line2.substr(col_first_i + 1,
                                     col_last_i - col_first_i - 1);

    std::time_t time_ = std::stoi(time_s);

    bfs::path path_(path_s);

    unsigned int row_ = std::stoi(row_s);

    unsigned int col_ = std::stoi(col_s);

    return VimFileMark(
        path_.filename().string(),
        path_.parent_path(),
        time_,
        row_,
        col_
    );
}

std::string  VimFileMark::getFileName() {
    return this->filename_;
}

std::time_t  VimFileMark::getTime() {
    return this->time_;
}

bfs::path    VimFileMark::getPath() {
    return this->path_;
}

unsigned int VimFileMark::getRow() {
    return this->posRow_;
}

unsigned int VimFileMark::getColumn() {
    return this->posCol_;
}
