#include "JsonSaver.h"

void JsonSaver::saveCommamdsHistory(const std::vector<std::pair<std::string,
                                 std::pair<bfs::path, std::time_t>>>& history) {

    std::ofstream out("history/commands_history.json", std::ofstream::out |
                      std::ofstream::trunc);
                      
    nlohmann::json commands = nlohmann::json::array();

    for (unsigned int i = 0; i < history.size(); i++) {
        std::string time = std::asctime(
            std::localtime(&history[i].second.second)
        );

        time = time.substr(0, time.length() - 1);
        nlohmann::json obj = nlohmann::json::object ({
            {"time", time},
            {"path", history[i].second.first.string()},
            {"command", history[i].first}
        });
        commands.push_back(obj);
    }

    out << std::setw(4) << commands;

    out.close();
}

void JsonSaver::saveFilesystemsHistory(const std::vector<std::pair<bfs::path,
                                                       std::time_t>>& history) {

    std::ofstream out("history/filesystems_history.json", std::ofstream::out |
                      std::ofstream::trunc);

    nlohmann::json files = nlohmann::json::array();

    for (unsigned int i = 0; i < history.size(); i++) {
        std::string time = std::asctime(std::localtime(&history[i].second));

        time = time.substr(0, time.length() - 1);

        nlohmann::json obj = nlohmann::json::object({
          {"time", time},
          {"path", history[i].first.string()}
        });

        files.push_back(obj);
    }

    out << std::setw(4) <<files;

    out.close();
}
