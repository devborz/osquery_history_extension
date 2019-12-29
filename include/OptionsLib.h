#pragma once

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <map>

namespace bpo = boost::program_options;

enum Option {
    all,
    filesystem,
    bash,
    vim,
    help
};

class Options {
public:
    static Option parse(const std::string&);


    static void getOptions(bpo::options_description&);


    static void notifyOptionError(const std::string&);


    static void getHelp(bpo::options_description& desc);


    static Option readOption(const bpo::variables_map&, unsigned int&);
};
