#include "JsonSaver.h"

void JsonSaver::saveCommamdsHistory(const std::vector<std::pair<std::string,
                                 std::pair<bfs::path, std::time_t>>>& history) {

    std::ofstream out("history/commands_history.json", std::ofstream::out |
                      std::ofstream::trunc);

    out << "[\n";
    for (int i = 0; i < history.size(); i++) {
        out << "    "  << "{ \"time\" : \"" << std::put_time(
            std::localtime(&history[i].second.second), "%c %Z")
            << "\", \"path\": "    << history[i].second.first
            << ", \"command\": \"" << history[i].first << "\" }";

        if (i != history.size() - 1) {
            out << ",";
        }

        out << "\n";
    }
    out << "]\n";
    out.close();
}

void JsonSaver::saveFilesystemsHistory(const std::vector<std::pair<bfs::path,
                                                       std::time_t>>& history) {

    std::ofstream out("history/filesystems_history.json", std::ofstream::out |
                      std::ofstream::trunc);

    out << "[\n";
    for (int i = 0; i < history.size(); i++) {
       out << "    "  << "{ \"time\" : \"" << std::put_time(
           std::localtime(&history[i].second), "%c %Z")
           << "\", \"path\": "    << history[i].first << " }";

       if (i != history.size() - 1) {
           out << ",";
       }

       out << "\n";
    }
    out << "]\n";
    out.close();
}
