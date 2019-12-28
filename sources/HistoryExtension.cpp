#include "HistoryExtension.h"

void HistoryExtension::work(int argc, char* argv[]) {

    bpo::options_description desc;
    HistoryExtension::getOptions(desc);

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    unsigned int option_ec = 0;

    Option option = HistoryExtension::readOption(vm, option_ec);
    if (option_ec == 1) {
        return;
    }

    bfs::path path = HistoryExtension::getPath();

    switch (option) {
        case filesystem : {
            HistoryExtension::getFilesystemHistory(path);
            break;
        }
        case bash : {
            HistoryExtension::getBashHistory();
            break;
        }
        case vim : {
            HistoryExtension::getVimHistory();
            break;
        }
        case help : {
            HistoryExtension::getHelp(desc);
            break;
        }
    }
}

void HistoryExtension::getBashHistory() {

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

                if (ExecutedCommand::parseEvent(event_, command_,
                                                path_, time_)) {

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

            JsonSaver::saveFilesystemHistory(recentlyChangedFiles);
        }
        else {

            std::string message = "There are no changed files for this period";

            HistoryExtension::notify(message);
        }
    }
}

void HistoryExtension::getVimHistory() {

}

void HistoryExtension::notify(const std::string& message) {
    std::cerr << std::endl << message << std::endl;
}

void HistoryExtension::getOptions(bpo::options_description& desc) {
    desc.add_options()
        ("help", "outputs help message")
        ("filesystem", "outputs filesystem's history")
        ("bash", "outputs bash history")
        ("vim", "outputs vim history")
    ;
}

void HistoryExtension::notifyOptionError(const std::string& option) {
    std::cerr << "Option \'" << option << "\' does not exist. See 'help'\n";
}

void HistoryExtension::getHelp(bpo::options_description& desc) {
    std::cout << "\nOptions:\n" << desc << std::endl;
}

Option HistoryExtension::readOption(const bpo::variables_map& vm,
                                      unsigned int& ec) {
    std::string option_;

    if (vm.count("filesystem"))
        option_ = "filesystem";
    else if (vm.count("bash"))
        option_ = "bash";
    else if (vm.count("vim"))
        option_ = "vim";
    else if (vm.count("help"))
        option_ = "help";

    Option option = Options::parse(option_);

    bool isValid = option == filesystem || option == bash ||
                   option == help || option == vim;

    if (!isValid) {
      HistoryExtension::notifyOptionError(option_);
      ec = 1;
    }

    return option;
}

bfs::path HistoryExtension::getPath() {
    std::string path_ = getenv("HOME");

    bfs::path pathToDir(path_);

    return pathToDir;
}
