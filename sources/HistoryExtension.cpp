#include "HistoryExtension.h"

void HistoryExtension::work(int argc, char* argv[]) {
  bpo::options_description desc;
  Options::getOptions(desc);

  bpo::variables_map vm;
  bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
  bpo::notify(vm);

  unsigned int option_ec = 0;

  std::shared_ptr<std::vector<Option>> options =
      Options::readOption(vm, option_ec);
  if (option_ec == 1) {
    return;
  }
  for (const auto& opt : *options) {
    switch (opt) {
      case all: {
        HistoryExtension::getFilesystemHistory();

        HistoryExtension::getBashHistory();

        HistoryExtension::getVimHistory();

        break;
      }
      case filesystem: {
        HistoryExtension::getFilesystemHistory();

        break;
      }
      case bash: {
        HistoryExtension::getBashHistory();

        break;
      }
      case vim: {
        HistoryExtension::getVimHistory();

        break;
      }
      case help: {
        Options::getHelp(desc);

        break;
      }
    }
  }
}

void HistoryExtension::getBashHistory() {
  std::string pathToFile = getenv("HOME") + std::string("/bash-history.log");

  std::ifstream bashHistory(pathToFile);

  std::vector<ExecutedCommand> history;

  if (bashHistory.is_open()) {
    while (!bashHistory.eof()) {
      std::time_t time_;

      bfs::path path_;

      std::string command_;

      std::string event_;

      std::getline(bashHistory, event_);

      if (event_.length() >= 20) {
        if (ExecutedCommand::parseEvent(event_, command_, path_, time_)) {
          history.push_back(ExecutedCommand(command_, path_, time_));
        }
      }
    }

    bashHistory.close();

    if (!history.empty()) {
      JsonSerializer::saveBashHistory(history);
    } else {
      char message[] = "The bash history is empty";
      HistoryExtension::notify(std::string(message));
    }

  } else {
    std::string error_message = "File " + pathToFile + " wasn't found";
    throw std::logic_error(error_message);
  }
}

void HistoryExtension::iterate(bfs::path pathToDir,
                               std::vector<ChangedFile>& list) {
  for (const bfs::directory_entry& pathToObj :
       bfs::directory_iterator(pathToDir)) {
    try {
      if (bfs::is_regular_file(pathToObj)) {
        Files::pushToList(pathToObj, list);

      } else if (bfs::is_directory(pathToObj)) {
        if (bfs::path(pathToObj).filename().string()[0] != '.') {
          HistoryExtension::iterate(pathToObj, list);
        }
      }
    } catch (const bfs::filesystem_error& e) {
      std::cout << e.what() << std::endl;
    }
  }
}

void HistoryExtension::getFilesystemHistory() {
  std::vector<ChangedFile> recentlyChangedFiles;

  bfs::path pathToDir = HistoryExtension::getPath();

  if (bfs::exists(pathToDir)) {
    HistoryExtension::iterate(pathToDir, recentlyChangedFiles);

    if (!recentlyChangedFiles.empty()) {
      Files::sortByTime(recentlyChangedFiles);

      JsonSerializer::saveFilesystemHistory(recentlyChangedFiles);
    } else {
      std::string message = "There are no changed files for this period";

      HistoryExtension::notify(message);
    }
  }
}

void HistoryExtension::getVimHistory() {
  std::vector<VimCommand> vimCommands;
  std::vector<VimFileMark> vimFileMarks;

  std::string pathToFile = getenv("HOME") + std::string("/.viminfo");

  std::ifstream viminfo(pathToFile);

  if (viminfo.is_open()) {
    bool readingCommandlineHistory = false;
    bool readingFileMarksHistory = false;

    std::string commandlineHistoryTitle =
        "# Command Line History (newest to oldest):";

    std::string fileMarksHistoryTitle = "# File marks:";

    while (!viminfo.eof()) {
      std::string line;
      std::getline(viminfo, line);

      if (line == commandlineHistoryTitle) {
        char sharp = '#';

        std::string command_;
        std::string info_;

        while (!viminfo.eof()) {
          std::getline(viminfo, command_);
          std::getline(viminfo, info_);

          if (info_.front() != sharp) {
            VimCommand command = VimCommand::parseCommand(command_, info_);
            vimCommands.insert(vimCommands.begin(), command);
          } else {
            line = info_;

            break;
          }
        }
      }
      if (line == fileMarksHistoryTitle) {
        char sharp = '#';

        std::string line1;
        std::string line2;

        while (!viminfo.eof()) {
          std::getline(viminfo, line1);
          std::getline(viminfo, line2);

          if (line2.front() != sharp) {
            VimFileMark fileMark = VimFileMark::parseFileMark(line1, line2);
            vimFileMarks.insert(vimFileMarks.begin(), fileMark);
          } else {
            break;
          }
        }
      }
    }
    viminfo.close();

    if (!vimCommands.empty()) {
      JsonSerializer::saveVimCommandsHistory(vimCommands);
    } else {
      std::string message = "Vim commands history is empty";
      HistoryExtension::notify(message);
    }

    if (!vimFileMarks.empty()) {
      JsonSerializer::saveVimFileMarksHistory(vimFileMarks);
    } else {
      std::string message = "Vim file marks history is empty";
      HistoryExtension::notify(message);
    }
  } else {
    std::string error_message = "File " + pathToFile + " wasn't found";
    throw std::logic_error(error_message);
  }
}

void HistoryExtension::notify(const std::string& message) {
  std::cerr << std::endl << message << std::endl;
}
