#include "command.h"

unsigned int findSpace(std::string& line) {
    char space = ' ';

    for(unsigned int i = 0; i < line.length(); i++) {
        if (line[i] == space) {
            return i;
        }
    }
    return 0;
}

unsigned int findSpace(std::string& line, const unsigned int& pos) {
    char space = ' ';

    for(unsigned int i = pos + 1; i < line.length(); i++) {
        if (line[i] == space) {
            return i;
        }
    }
    return 0;
}

Command Commands::parse(const std::string& command) {
    std::map<std::string, Command> commandsMap {
        std::make_pair("filesystem", filesystem),
        std::make_pair("commandline", commandline),
        std::make_pair("help", help)
    };

    return commandsMap[command];
}

void Commands::parseEvent(std::string& event, std::string& command,
                          fs::path& path, std::time_t& time) {
    event += " ";
    unsigned int s_1 = findSpace(event);
    unsigned int s_2 = findSpace(event, s_1);
    unsigned int s_3 = findSpace(event, s_2 + 1);

    std::string clock = event.substr(0, s_1);
    path = fs::path(event.substr(s_1 + 1, s_2 - s_1 - 1));
    command  = event.substr(s_3 + 2, event.length() - s_3 - 3);

    unsigned int year  = std::stoi(clock.substr(0, 4));
    unsigned int month = std::stoi(clock.substr(5, 2));
    unsigned int day   = std::stoi(clock.substr(8, 2));
    unsigned int hour  = std::stoi(clock.substr(11, 2));
    unsigned int min   = std::stoi(clock.substr(14, 2));
    unsigned int sec   = std::stoi(clock.substr(17, 2));

    struct std::tm t;
    t.tm_sec  = sec;
    t.tm_min  = min;
    t.tm_hour = hour;
    t.tm_mday = day;
    t.tm_mon  = month - 1;
    t.tm_year = year - 1900;

    time_t time_ = std::mktime(&t);
    time = time_;

}

void Commands::print(const std::vector<std::pair<std::string,
                     std::pair<fs::path, std::time_t>>>& events,
                     const fs::path& headPath) {
    for (const auto& e: events) {
        std::time_t time = e.second.second;

        std::cout <<  std::put_time(std::localtime(&time), "%c %Z") << "\t"
                  <<  fs::path(Commands::getRealtivePath(headPath,
                      e.second.first).string()+"/") << "\t" << e.first << "\n";
    }

}

fs::path Commands::getRealtivePath(const fs::path& parentPath,
                                const fs::path& childPath) {

    std::string parent = parentPath.relative_path().string();
    std::string child  = childPath.relative_path().string();

    char slash = '/';
    if (parent.back() != slash) {
        parent.append("/");
    }

    std::string difference = child.substr(parent.length(),
                                              child.length() - 1);

    fs::path relativePath = fs::path(difference);

    return relativePath;
}

bool Commands::isChildPath(const fs::path& parentPath,
                                const fs::path& path) {
    std::string parent = parentPath.string();
    std::string path_  = path.string();

    auto n = path_.find(parent);

    if(n != std::string::npos) {
        return true;
    }
    else {
        return false;
    }
}
