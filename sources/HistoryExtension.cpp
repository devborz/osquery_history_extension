#include "HistoryExtension.h"

void HistoryExtension::startListening(int argc, char* argv[]) {
    options_description desc;
    options_description parameters;

    getCommand(desc, parameters);
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);


    std::string command_;
    if (vm.count("filesystem"))
        command_ = "filesystem";
    else if (vm.count("commandline"))
        command_ = "commandline";
    else if (vm.count("help"))
        command_ = "help";

    Command command = Commands::parse(command_);

    switch (command) {
        case filesystem : {

            std::string path_;
            if (vm.count("path")) {
                path_ = vm["path"].as<std::string>();
            }
            else {
                path_ = getenv("HOME");
            }

            filesys::path pathToDir(path_);

            if(!exists(pathToDir)) {
                notifyPathError(path_);
                break;
            }

            std::string period_;

            if (vm.count("path")) {
                period_ = vm["period"].as<std::string>();
            }
            else {
                period_ = "h";
            }

            Period period = Periods::parse(period_);
            bool isValid = isValidPeriod(period);

            if (!isValid) {
                HistoryExtension::notifyPeriodError(period_);
                break;
            }

            getFilesystemHistory(pathToDir, period);
            break;
        }
        case commandline : {
            std::string period_;

            if (vm.count("path")) {
                period_ = vm["period"].as<std::string>();
            }
            else {
                period_ = "h";
            }

            Period period = Periods::parse(period_);
            bool isValid = isValidPeriod(period);

            if (!isValid) {
                HistoryExtension::notifyPeriodError(period_);
                break;
            }

            getConsoleHistory(period);
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

/*void HistoryExtension::getActionsHistory(const Period& period) {

}*/

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

void HistoryExtension::getCommand(options_description& desc,
                                               options_description& parameters) {
    desc.add_options()
        ("help", "give list of recently changed files")
        ("filesystem", "outputs filesystem's history")
        ("commandline", "outputs commandline's history")
        ("path", value<std::string>(), "add path to directory")
        ("period", value<std::string>(), "add period of history")
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

void HistoryExtension::getHelp(options_description& desc) {
    std::cout << "\nOptions:\n" << desc << std::endl;

    std::cout << "\nPeriods:\n" << std::setw(12) << "--period=h" << "\tlast hour\n"
                                << std::setw(12) << "--period=d" << "\tlast day\n"
                                << std::setw(12) << "--period=w" << "\tlast week\n"
                                << std::setw(12) << "--period=m" << "\tlast month\n"
                                << std::setw(12) << "--period=a" << "\tall time\n";
}
