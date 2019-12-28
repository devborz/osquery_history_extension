#include "CommandsLib.h"

Command Commands::parse(const std::string& command) {
    std::map<std::string, Command> commandsMap {
        std::make_pair("filesystem", filesystem),
        std::make_pair("bash", bash),
        std::make_pair("vim", vim),
        std::make_pair("help", help)
    };

    return commandsMap[command];
}
