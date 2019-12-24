#include "HistoryExtension.h"

void HistoryExtension::listen(int argc, char* argv[]) {
    bpo::options_description desc;
    HistoryExtension::getCommand(desc);

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    unsigned int command_ec = 0;
    unsigned int path_ec    = 0;
    unsigned int period_ec  = 0;

    Command command = HistoryExtension::readCommand(vm, command_ec);
    if (command_ec == 1) {
        return;
    }

    bfs::path path = HistoryExtension::readPath(vm, path_ec);
    if (path_ec == 1) {
        return;
    }

    Period period = HistoryExtension::readPeriod(vm, period_ec);
    if (period_ec == 1) {
        return;
    }

    bool isRecursive = HistoryExtension::isRecursive(vm);

    switch (command) {
        case filesystem : {
            getFilesystemHistory(path, period, isRecursive);
            break;
        }
        case commandline : {
            getConsoleHistory(path, period, isRecursive);
            break;
        }
        case help : {
            HistoryExtension::getHelp(desc);
            break;
        }
    }
}

void HistoryExtension::getConsoleHistory(const bfs::path& path,
                                         const Period& period,
                                         const bool& isRecursive) {

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

                    if (isRecursive) {
                        if (Commands::isChildPath(path, childpair.first)) {
                            events.push_back(pair);
                        }
                    }
                    else {
                        if (path.relative_path() ==
                            childpair.first.relative_path()) {
                            events.push_back(pair);
                        }
                    }
                }
            }
        }

        bashHistory.close();

        if (events.size() != 0) {
            Commands::print(events, path);
        }
        else {
            char message[] = "The command line history for this period is empty";
            HistoryExtension::notify(std::string(message));
        }
    }
    else {
        throw std::logic_error("File wasn't found");
    }
}

void HistoryExtension::iterate(bfs::path pathToDir,
                        std::vector<std::pair<bfs::path, std::time_t>>& list) {


    for (const bfs::directory_entry& pathToObj :
         bfs::directory_iterator(pathToDir)) {
        try{
            if (bfs::is_regular_file(pathToObj)) {
                bool isRecentlyChanged =
                    Files::checkIsRecentlyChanged(pathToObj, LAST_HOUR);

                if (isRecentlyChanged) {
                    Files::pushToList(pathToObj, list);
                }
            }
            else if (bfs::is_directory(pathToObj)) {
                HistoryExtension::iterate(pathToObj, list);
            }
        }
        catch (const bfs::filesystem_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void HistoryExtension::getFilesystemHistory(const bfs::path& pathToDir,
                                            const Period& period,
                                            const bool& isRecursive) {
    std::vector<std::pair<bfs::path, std::time_t>> recentlyChangedFiles;
    std::vector<std::shared_ptr<std::thread>> threads;

    if (bfs::exists(pathToDir)) {
        HistoryExtension::iterate(pathToDir, recentlyChangedFiles);

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
        ("r", " recursively")
    ;
}

void HistoryExtension::notifyCommandError(const std::string& invalidCommand) {
    std::cerr << "Command \'" << invalidCommand
                << "\' does not exist. See 'help'\n";
}

void HistoryExtension::notifyPathError(const std::string& invalidPath) {
    std::cerr << "Path \'" << invalidPath
                << "\' does not exist. See 'help'\n";
}

void HistoryExtension::notifyPeriodError(const std::string& invalidPeriod) {
    std::cerr << "Period \'" << invalidPeriod
                << "\' does not exist. See 'help'\n";
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

Command HistoryExtension::readCommand(const bpo::variables_map& vm,
                                      unsigned int& ec) {
    std::string command_;

    if (vm.count("filesystem"))
      command_ = "filesystem";
    else if (vm.count("commandline"))
      command_ = "commandline";
    else if (vm.count("help"))
      command_ = "help";

    Command command = Commands::parse(command_);

    bool isValid = command == filesystem || command == commandline ||
                   command == help;

    if (!isValid) {
      HistoryExtension::notifyCommandError(command_);
      ec = 1;
    }

    return command;
}

bfs::path HistoryExtension::readPath(const bpo::variables_map& vm,
                                      unsigned int& ec) {
    /*std::string path_;

    if (vm.count("path")) {
      path_ = vm["path"].as<std::string>();
    }
    else {
      path_ = getenv("HOME");
    }

    bfs::path pathToDir(path_);

    if(!bfs::exists(pathToDir)) {
      notifyPathError(path_);
      ec = 1;
  }*/
    std::string path_ = "/mnt/c/Users/Usman/workspace";
    bfs::path pathToDir(path_);

    return pathToDir;
}

Period HistoryExtension::readPeriod(const bpo::variables_map& vm,
                                      unsigned int& ec) {
    std::string period_;

    if (vm.count("period")) {
      period_ = vm["period"].as<std::string>();
    }
    else {
      period_ = "h";
    }

    Period period = Periods::parse(period_);

    bool isValid = Periods::isValidPeriod(period);

    if (!isValid) {
      HistoryExtension::notifyPeriodError(period_);
      ec = 1;
    }

    return period;
}

bool HistoryExtension::isRecursive(const bpo::variables_map& vm) {
    return vm.count("r");
}
