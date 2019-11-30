#pragma once

#include <fstream>
#include <iostream>
#include <string>

enum Period {
    LAST_HOUR,
    LAST_DAY,
    LAST_WEEK,
    LAST_MONTH,
    ALL
};

class HistoryExtension {
private:
    //const ofstream* out;
    std::string username;

public:
    static void startListening();

    static void getConsoleHistory(const Period& period);

    static void getActionsHistory(const Period& period);

    static void getFilesystemHistory(const Period& period);
};
