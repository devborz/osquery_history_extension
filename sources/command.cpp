#include "command.h"

Command Commands::parse(std::string command) {
    std::map<std::string, Command> commandsMap {
        std::make_pair("filesystem", filesystem),
        std::make_pair("commandline", commandline)
    };

    return commandsMap[command];
}