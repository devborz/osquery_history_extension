#include "ChangedFile.h"

ChangedFile::ChangedFile(const std::string& fileName, const bfs::path& path,
                         const std::time_t& time) {
  this->fileName_ = fileName;
  this->path_ = path;
  this->time_ = time;
}
