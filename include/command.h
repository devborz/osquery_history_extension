#pragma once

#include <string>
#include <map>

enum Command {
    filesystem,
    commandline
};

class Commands {
public:
    static Command parse(std::string command);
};
