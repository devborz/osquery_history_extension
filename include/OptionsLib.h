#pragma once

#include <iostream>
#include <string>
#include <map>

enum Option {
    filesystem,
    bash,
    vim,
    help
};

class Options {
public:
    static Option parse(const std::string&);
};
