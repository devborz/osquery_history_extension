#include "OptionsLib.h"

Option Options::parse(const std::string& option) {
    std::map<std::string, Option> optionsMap {
        std::make_pair("filesystem", filesystem),
        std::make_pair("bash", bash),
        std::make_pair("vim", vim),
        std::make_pair("help", help)
    };

    return optionsMap[option];
}
