#include "HistoryExtension.h"

void HistoryExtension::startListening() {
    while(true) {
        std::string command_;
        std::cout << "\n>>> ";
        std::cin >> command_;
        if (!command_.empty()) {
            Command command = Commands::parse(command_);

            switch (command) {
                case filesystem : {
                    std::string path_;
                    std::cin >> path_;

                    if (path_.empty()) {
                        path_ = getenv("HOME");
                    }
                    filesys::path pathToDir(path_);

                    std::string period_;
                    std::cin >> period_;
                    if (period_.empty()) {
                        period_ = "-h";
                    }

                    Period period = Periods::parse(period_);
                    bool isValid = (period == LAST_HOUR) || (period == LAST_DAY)
                              || (period == LAST_WEEK) || (period == LAST_MONTH)
                              ||(period == ALL);

                    if (!isValid) {
                        std::cerr << "\'" << period
                                  << "\' is not period. See 'help'";
                        break;
                    }

                    getFilesystemHistory(pathToDir, period);
                    break;
                }
                case commandline : {
                    std::string period_;
                    std::cin >> period_;
                    if (period_.empty()) {
                        period_ = "-h";
                    }

                    Period period = Periods::parse(period_);
                    bool isValid = (period == LAST_HOUR) || (period == LAST_DAY)
                              || (period == LAST_WEEK) || (period == LAST_MONTH)
                              ||(period == ALL);

                    if (!isValid) {
                        std::cerr << "\'" << period
                                  << "\' is not period. See 'help'";
                        break;
                    }

                    getConsoleHistory(period);
                    break;
                }
                case help : {
                    std::cout << "\nCommands:\n filesystem ${PATH_TO_DIRECTORY}"
                         << " ${PERIOD} - give list of recently changed files"
                         << "\n commandline ${PERIOD} - give history of "
                         << "command line"
                         << "\n "
                         << "\nPeriods:\n -h -- last hour\n -d -- last day"
                         << "\n -w -- last week\n -m -- last month\n -a -- all";
                    break;
                }
                default : {
                    std::cerr << "\'" << command
                              << "\' is not command. See 'help'";
                }
            }
        }
    }
}

void HistoryExtension::getConsoleHistory(const Period& period) {
    std::string homePath = getenv("HOME");
    std::ifstream bashHistory(homePath + "/.bash_history");

    if (bashHistory.is_open()) {
        while (!bashHistory.eof()) {
            std::string command;
            std::getline(bashHistory, command);
            std::cout << command << std::endl;
        }
        bashHistory.close();
    }
    else {
        throw std::logic_error("File wasn't found");
    }
}

void HistoryExtension::getActionsHistory(const Period& period) {

}

void HistoryExtension::getFilesystemHistory(const filesys::path& pathToDir,
                                        const Period& period) {
    std::vector<std::pair<filesys::path, std::time_t>> recentlyChangedFiles;
    if (exists(pathToDir)) {
        for (const filesys::directory_entry& pathToObj :
             filesys::recursive_directory_iterator(pathToDir)) {

            if (filesys::is_regular_file(pathToObj)) {
                bool isRecentlyChanged =
                    Files::checkIsRecentlyChanged(pathToObj, period);

                if (isRecentlyChanged) {
                    Files::pushToList(pathToObj, recentlyChangedFiles);
                }
            }
        }
        Files::sortByTime(recentlyChangedFiles);
        Files::print(recentlyChangedFiles);
    }


}
