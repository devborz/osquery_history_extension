#pragma once

#include <iostream>
#include <string>
#include <map>

enum Command {
    filesystem,
    bash,
    vim,
    help
};

class Commands {
public:
    static Command parse(const std::string& command);
};
