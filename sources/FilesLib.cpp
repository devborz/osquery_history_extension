#include "FilesLib.h"

void Files::pushToList(const fs::path& pathToObj,
                       std::vector<ChangedFile>& recentlyChangedFiles) {
  auto fileLastChange = fs::last_write_time(pathToObj);

  std::time_t fileLastChangeTime = fileLastChange;

  recentlyChangedFiles.push_back(ChangedFile(pathToObj.filename().string(),
                                             pathToObj.parent_path(),
                                             fileLastChangeTime));
}

void Files::sortByTime(std::vector<ChangedFile>& recentlyChangedFiles) {
  auto size = recentlyChangedFiles.size();

  for (unsigned int i = 0; i < size - 1; i++) {
    for (unsigned int j = 0; j < size - i - 1; j++) {
      if (recentlyChangedFiles[j].getTime() >
          recentlyChangedFiles[j + 1].getTime()) {
        auto temp = recentlyChangedFiles[j];
        recentlyChangedFiles[j] = recentlyChangedFiles[j + 1];
        recentlyChangedFiles[j + 1] = temp;
      }
    }
  }
}
