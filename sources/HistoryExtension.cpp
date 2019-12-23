#include "HistoryExtension.h"

void HistoryExtension::listen(int argc, char* argv[]) {
    bpo::options_description desc;

    HistoryExtension::getCommand(desc);
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);


    std::string command_;
    if (vm.count("filesystem"))
        command_ = "filesystem";
    else if (vm.count("commandline"))
        command_ = "commandline";
    else if (vm.count("help"))
        command_ = "help";

    Command command = Commands::parse(command_);

    std::string path_;

    if (vm.count("path")) {
        path_ = vm["path"].as<std::string>();
    }
    else {
        path_ = getenv("HOME");
    }

    bfs::path pathToDir(path_);

    if(!bfs::exists(pathToDir)) {
        notifyPathError(path_);
        return;
    }

    std::string period_;

    if (vm.count("period")) {
        period_ = vm["period"].as<std::string>();
    }
    else {
        period_ = "h";
    }

    Period period = Periods::parse(period_);
    bool isValid = isValidPeriod(period);

    if (!isValid) {
        HistoryExtension::notifyPeriodError(period_);
        return;
    }

    bool isSearchRecursive = false;

    if (vm.count("r")) {
        isSearchRecursive = true;
    }

    switch (command) {
        case filesystem : {
            getFilesystemHistory(pathToDir, period, isSearchRecursive);
            break;
        }
        case commandline : {
            getConsoleHistory(pathToDir, period);
            break;
        }
        case help : {
            HistoryExtension::getHelp(desc);
            break;
        }
        default : {
            HistoryExtension::notifyCommandError(command_);
        }
    }
}

void HistoryExtension::getConsoleHistory(const bfs::path& path,
                                         const Period& period) {

    std::time_t period_ = Periods::parseTime(period);

    std::string homePath = getenv("HOME");

    std::ifstream bashHistory(homePath + "/bash-history.log");
    std::vector<std::pair<std::string, std::pair<bfs::path,
                std::time_t>>> events;
    if (bashHistory.is_open()) {
        while (!bashHistory.eof()) {
            std::time_t time;
            bfs::path path_;
            std::string command;
            std::string event;

            std::getline(bashHistory, event);
            if (event.length() >= 18) {
                Commands::parseEvent(event, command, path_, time);

                std::time_t now = std::chrono::system_clock::to_time_t(
                                  std::chrono::system_clock::now()
                                  );

                if (now - time <= period_) {

                    std::pair<bfs::path, std::time_t> childpair(path_, time);
                    std::pair<std::string, std::pair<bfs::path,
                                std::time_t>> pair(command, childpair);
                    if (Commands::isChildPath(path, childpair.first)) {
                        events.push_back(pair);
                    }
                }
            }
        }
        bashHistory.close();
        if (events.size() != 0) {
            Commands::print(events, path);
        }
        else {
            std::string message = "The command line history for this period is empty";
            HistoryExtension::notify(message);
        }
    }
    else {
        throw std::logic_error("File wasn't found");
    }
}

void HistoryExtension::getFilesystemHistory(const bfs::path& pathToDir,
                                            const Period& period,
                                            const bool& isSearchRecursive) {
    std::vector<std::pair<bfs::path, std::time_t>> recentlyChangedFiles;

    if (bfs::exists(pathToDir)) {
        if (isSearchRecursive) {
            for (const bfs::directory_entry& pathToObj :
                 bfs::recursive_directory_iterator(pathToDir)) {

                if (bfs::is_regular_file(pathToObj)) {
                    bool isRecentlyChanged =
                        Files::checkIsRecentlyChanged(pathToObj, period);

                    if (isRecentlyChanged) {
                        Files::pushToList(pathToObj, recentlyChangedFiles);
                    }
                }
            }
        }
        else {
            for (const bfs::directory_entry& pathToObj :
                 bfs::directory_iterator(pathToDir)) {

                if (bfs::is_regular_file(pathToObj)) {
                    bool isRecentlyChanged =
                        Files::checkIsRecentlyChanged(pathToObj, period);

                    if (isRecentlyChanged) {
                        Files::pushToList(pathToObj, recentlyChangedFiles);
                    }
                }
            }
        }

        if (recentlyChangedFiles.size() != 0) {
            Files::sortByTime(recentlyChangedFiles);
            Files::print(recentlyChangedFiles, pathToDir);
        }
        else {
            std::string message = "There are no changed files for this period";
            HistoryExtension::notify(message);
        }
    }
}

void HistoryExtension::notify(const std::string& message) {
    std::cerr << std::endl << message << std::endl;
}

void HistoryExtension::getCommand(bpo::options_description& desc) {
    desc.add_options()
        ("help", "give list of recently changed files")
        ("filesystem", "outputs filesystem's history")
        ("commandline", "outputs commandline's history")
        ("path", bpo::value<std::string>(), "add path to directory")
        ("period", bpo::value<std::string>(), "add period of history")
        ("r", "search recursively")
    ;
}

void HistoryExtension::notifyCommandError(const std::string& invalidCommand) {
    std::cerr << "Command \'" << invalidCommand
              << "\' does not exist. See 'help'";
}

void HistoryExtension::notifyPathError(const std::string& invalidPath) {
    std::cerr << "Path \'" << invalidPath
              << "\' does not exist. See 'help'";
}

void HistoryExtension::notifyPeriodError(const std::string& invalidPeriod) {
    std::cerr << "Period \'" << invalidPeriod
              << "\' does not exist. See 'help'";
}

bool HistoryExtension::isValidPeriod(const Period& period) {
    bool isValid = (period == LAST_HOUR) || (period == LAST_DAY)
              || (period == LAST_WEEK) || (period == LAST_MONTH)
              ||(period == ALL);

    return isValid;
}

void HistoryExtension::getHelp(bpo::options_description& desc) {
    std::cout << "\nOptions:\n" << desc << std::endl;

    std::cout << "Periods:\n" << std::setw(12)
                                            << "--period=h" << "\tlast hour\n"
                              << std::setw(12)
                                            << "--period=d" << "\tlast day\n"
                              << std::setw(12)
                                            << "--period=w" << "\tlast week\n"
                              << std::setw(12)
                                            << "--period=m" << "\tlast month\n"
                              << std::setw(12)
                                            << "--period=a" << "\tall time\n";
}

void HistoryExtension::checkBashConfig() {
    std::string homePath = getenv("HOME");
    std::string config;

    std::ifstream bashConfig("config/config.txt");
    if (bashConfig.is_open()) {
        std::string line;
        std::getline(bashConfig, line);
        config = line;

        bashConfig.close();
    }
    else {
        throw std::logic_error("File wasn't found");
    }

    std::string profile;
    if (bfs::exists(homePath + "/.profile")) {
        profile = "/.profile";
    }
    else {
        profile = "/.bash_profile";
    }
    std::ifstream bashProfile(homePath + profile);
    bool haveConfig = false;

    if (bashProfile.is_open()) {
        while (!bashProfile.eof()) {
            std::string line;
            std::getline(bashProfile, line);
            if (line == config) {
                haveConfig = true;
            }
        }
        bashProfile.close();
    }
    else {
        throw std::logic_error("File wasn't found");
    }

    if (!haveConfig) {
        std::ofstream bashProfile(homePath + profile);
        if (bashProfile.is_open()) {
            while (!bashProfile.eof()) {
                bashProfile << config;
            }
            bashProfile.close();
        }
        else {
            throw std::logic_error("File wasn't found");
        }
    }
}
