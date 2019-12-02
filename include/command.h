#pragma once

#include <string>
#include <map>

enum Command {
    filesystem,
    commandline,
    help
};

class Commands {
public:
    static Command parse(std::string command);
};
