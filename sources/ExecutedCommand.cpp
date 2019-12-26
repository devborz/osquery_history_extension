#include <ExecutedCommand.h>

ExecutedCommand::ExecutedCommand(const std::string& command,
                                 const bfs::path& path,
                                 const std::time_t& time) {
    this->command_ = command;
    this->path_ = path;
    this->time_ = time;
}

std::string ExecutedCommand::getCommand() {
    return this->command_;
}

bfs::path ExecutedCommand::getPath() {
    return this->path_;
}

std::time_t ExecutedCommand::getTime() {
    return this->time_;
}
