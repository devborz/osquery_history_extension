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
        case commandline : {
            getCommandlineHistory(path);
            break;
        }
        case help : {
            HistoryExtension::getHelp(desc);
            break;
        }
    }
}

void HistoryExtension::getCommandlineHistory(const bfs::path& path) {

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

            if (event.length() >= 20) {

                if (Commands::parseEvent(event, command, path_, time)) {

                    std::pair<bfs::path, std::time_t> childpair(path_, time);

                    std::pair<std::string, std::pair<bfs::path,
                                std::time_t>> pair(command, childpair);

                    events.push_back(pair);
                }
            }
        }

        bashHistory.close();

        if (events.size() != 0) {
            JsonSaver::saveCommamdsHistory(events);
        }
        else {
            char message[] = "The command line history is empty";
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
    std::vector<std::pair<bfs::path, std::time_t>> recentlyChangedFiles;

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
        ("commandline", "outputs commandline's history")
    ;
}

void HistoryExtension::notifyCommandError(const std::string& command) {
    std::cerr << "Command \'" << command << "\' does not exist. See 'help'\n";
}

void HistoryExtension::getHelp(bpo::options_description& desc) {
    std::cout << "\nOptions:\n" << desc << std::endl;
}

// void HistoryExtension::checkBashConfig() {
//     std::string homePath = getenv("HOME");
//
//     std::string config;
//
//     std::ifstream bashConfig("config/config.txt");
//     std::cerr << "here";
//     if (bashConfig.is_open()) {
//         std::string line;
//         std::getline(bashConfig, line);
//         config = line;
//         std::cerr << line;
//         bashConfig.close();
//     }
//     else {
//         throw std::logic_error("File wasn't found");
//     }
//
//     std::string profile;
//
//     if (bfs::exists(homePath + "/profile.txt")) {
//         profile = "/profile.txt";
//     }
//     else {
//         profile = "/._bash_profile";
//     }
//
//     std::ifstream bashProfile_in(homePath + profile);
//
//     bool haveConfig = false;
//
//     if (bashProfile_in.is_open()) {
//         while (!bashProfile_in.eof()) {
//             std::string line;
//
//             std::getline(bashProfile_in, line);
//
//             if (line == config) {
//                 haveConfig = true;
//                 std::cerr << "\nTRUE\n";
//             }
//         }
//
//         bashProfile_in.close();
//     }
//     else {
//         throw std::logic_error("File wasn't found");
//     }
//     std::cerr << "\nHERE\n";
//     if (!haveConfig) {
//
//         std::ofstream bashProfile_out(homePath + profile, std::ios_base::app);
//
//         if (bashProfile_out.is_open()) {
//
//             while (!bashProfile_out.eof()) {
//                 bashProfile_out << config;
//             }
//             bashProfile_out.close();
//         }
//         else {
//             throw std::logic_error("File wasn't found");
//         }
//     }
// }

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

bfs::path HistoryExtension::getPath(const bpo::variables_map& vm) {
    std::string path_ = getenv("HOME");

    bfs::path pathToDir(path_);

    return pathToDir;
}
