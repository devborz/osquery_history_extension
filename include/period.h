#pragma once

#include <chrono>
#include <ctime>
#include <map>
#include <string>

enum Period {
    LAST_HOUR,
    LAST_DAY,
    LAST_WEEK,
    LAST_MONTH,
    ALL
};

class Periods {
public:
    static Period parse(const std::string& period);

    static std::time_t parseTime(const Period& period);
};
