#pragma once

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
    static Period parse(std::string period);
};
