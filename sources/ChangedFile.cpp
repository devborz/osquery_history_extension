#include "ChangedFile.h"

ChangedFile::ChangedFile(const std::string& fileName,
            const bfs::path& path,
            const std::time_t& time) {
    this->fileName_ = fileName;
    this->path_ = path;
    this->time_ = time;
}

std::string ChangedFile::getFileName() {
    return this->fileName_;
}

bfs::path   ChangedFile::getPath() {
    return this->path_;
}

std::time_t ChangedFile::getTime() {
    return this->time_;
}
