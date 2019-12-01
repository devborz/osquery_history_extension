#include "HistoryExtension.h"
#include <stdlib.h>

void HistoryExtension::startListening() {
    //this->username = getenv("USER");

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

void HistoryExtension::getFilesystemHistory(const Period& period) {

}
