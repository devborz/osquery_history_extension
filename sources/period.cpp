#include "period.h"

Period Periods::parse(std::string period) {
    std::map<std::string, Period> periodsMap {
        {"-h", LAST_HOUR},
        {"-d", LAST_DAY},
        {"-w", LAST_WEEK},
        {"-m", LAST_MONTH},
        {"-a", ALL}
    };

    return periodsMap[period];
}
