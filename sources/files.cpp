#include "files.h"

void Files::pushToList(const fs::path& pathToObj,
            std::vector<std::pair<fs::path, std::time_t>>& recentlyChangedFiles) {

    auto fileLastChange = fs::last_write_time(pathToObj);
    std::time_t fileLastChangeTime = fileLastChange;

    std::pair<fs::path, std::time_t> file(pathToObj, fileLastChangeTime);

    recentlyChangedFiles.push_back(file);
}

void Files::sortByTime(std::vector<std::pair<fs::path, std::time_t>>&
            recentlyChangedFiles) {
    auto size = recentlyChangedFiles.size();
    for (unsigned int i = 0; i < size - 1; i++) {
        for (unsigned int j = 0; j < size - i - 1; j++) {
            if (recentlyChangedFiles[j].second >
                recentlyChangedFiles[j + 1].second) {

                auto temp = recentlyChangedFiles[j];
                recentlyChangedFiles[j] = recentlyChangedFiles[j + 1];
                recentlyChangedFiles[j + 1] = temp;
            }
        }
    }
}

void Files::print(const std::vector<std::pair<fs::path, std::time_t>>&
                 recentlyChangedFiles,
                 const fs::path& headPath) {
    for (const std::pair<fs::path, std::time_t>& file : recentlyChangedFiles) {
        std::cout << std::put_time(std::localtime(&file.second), "%c %Z") <<
                     "\t" << Files::getRealtivePath(headPath, file.first) <<
                     std::endl;
    }
}

fs::path Files::getRealtivePath(const fs::path& parentPath,
                                const fs::path& childPath) {

    std::string parent = parentPath.relative_path().string();
    std::string child  = childPath.relative_path().string();

    std::string difference = child.substr(parent.length(),
                                              child.length() - 1);

    fs::path relativePath = fs::path(difference);

    return relativePath;
}
