#include "HistoryExtension.h"

void HistoryExtension::work(int argc, char* argv[]) {

    bpo::options_description desc;
    HistoryExtension::getCommand(desc);

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    unsigned int command_ec = 0;

    Command command = HistoryExtension::readCommand(vm, command_ec);
    if (command_ec == 1) {
        return;
    }

    bfs::path path = HistoryExtension::getPath(vm);

    switch (command) {
        case filesystem : {
            getFilesystemHistory(path);
            break;
        }
        case bash : {
            getBashHistory(path);
            break;
        }
        case help : {
            HistoryExtension::getHelp(desc);
            break;
        }
    }
}

void HistoryExtension::getBashHistory(const bfs::path& path) {

    std::string homePath = getenv("HOME");

    std::ifstream bashHistory(homePath + "/bash-history.log");

    std::vector<ExecutedCommand> history;

    if (bashHistory.is_open()) {

        while (!bashHistory.eof()) {

            std::time_t time_;

            bfs::path path_;

            std::string command_;

            std::string event_;

            std::getline(bashHistory, event_);

            if (event_.length() >= 20) {

                if (Commands::parseEvent(event_, command_, path_, time_)) {

                    history.push_back(ExecutedCommand(command_, path_, time_));
                }
            }
        }

        bashHistory.close();

        if (history.size() != 0) {
            JsonSaver::saveBashHistory(history);
        }
        else {
            char message[] = "The bash history is empty";
            HistoryExtension::notify(std::string(message));
        }

    }
    else {
        throw std::logic_error("File wasn't found");
    }
}

void HistoryExtension::iterate(bfs::path pathToDir,
                               std::vector<ChangedFile>& list) {


    for (const bfs::directory_entry& pathToObj :
         bfs::directory_iterator(pathToDir)) {

        try {

            if (bfs::is_regular_file(pathToObj)) {

                Files::pushToList(pathToObj, list);

            }
            else if (bfs::is_directory(pathToObj)) {

                if (bfs::path(pathToObj).filename().string()[0] != '.') {
                    HistoryExtension::iterate(pathToObj, list);
                }

            }

        }
        catch (const bfs::filesystem_error& e) {
            std::cout << e.what() << std::endl;
        }

    }
}

void HistoryExtension::getFilesystemHistory(const bfs::path& pathToDir) {
    std::vector<ChangedFile> recentlyChangedFiles;

    if (bfs::exists(pathToDir)) {

        HistoryExtension::iterate(pathToDir, recentlyChangedFiles);

        if (recentlyChangedFiles.size() != 0) {

            Files::sortByTime(recentlyChangedFiles);

            JsonSaver::saveFilesystemsHistory(recentlyChangedFiles);
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
        ("help", "outputs help message")
        ("filesystem", "outputs filesystem's history")
        ("bash", "outputs bash history")
    ;
}

void HistoryExtension::notifyCommandError(const std::string& command) {
    std::cerr << "Command \'" << command << "\' does not exist. See 'help'\n";
}

void HistoryExtension::getHelp(bpo::options_description& desc) {
    std::cout << "\nOptions:\n" << desc << std::endl;
}

Command HistoryExtension::readCommand(const bpo::variables_map& vm,
                                      unsigned int& ec) {
    std::string command_;

    if (vm.count("filesystem"))
      command_ = "filesystem";
    else if (vm.count("bash"))
      command_ = "bash";
    else if (vm.count("help"))
      command_ = "help";

    Command command = Commands::parse(command_);

    bool isValid = command == filesystem || command == bash ||
                   command == help;

    if (!isValid) {
      HistoryExtension::notifyCommandError(command_);
      ec = 1;
    }

    return command;
}

bfs::path HistoryExtension::getPath(const bpo::variables_map& vm) {
    std::string path_ = getenv("HOME");

    bfs::path pathToDir(path_);

    return pathToDir;
}
