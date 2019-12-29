#include "OptionsLib.h"

Option Options::parse(const std::string& option) {
    std::map<std::string, Option> optionsMap {
        std::make_pair("all", all),
        std::make_pair("filesystem", filesystem),
        std::make_pair("bash", bash),
        std::make_pair("vim", vim),
        std::make_pair("help", help)
    };

    return optionsMap[option];
}

void Options::notifyOptionError(const std::string& option) {
    std::cerr << "Option \'" << option << "\' does not exist. See 'help'\n";
}

void Options::getHelp(bpo::options_description& desc) {
    std::cout << "\nOptions:\n" << desc << std::endl;
}

Option Options::readOption(const bpo::variables_map& vm,
                                    unsigned int& ec) {
    std::string option_;

    if (vm.count("filesystem"))
        option_ = "filesystem";
    else if (vm.count("bash"))
        option_ = "bash";
    else if (vm.count("vim"))
        option_ = "vim";
    else if (vm.count("help"))
        option_ = "help";
    else if (vm.count("all"))
        option_ = "all";

    Option option = Options::parse(option_);

    bool isValid = option == filesystem || option == bash ||
                   option == help || option == vim || option == all;

    if (!isValid) {
      Options::notifyOptionError(option_);
      ec = 1;
    }

    return option;
}

void Options::getOptions(bpo::options_description& desc) {
    desc.add_options()
        ("help", "outputs help message")
        ("filesystem", "updates filesystem's history")
        ("bash", "updates bash history's file")
        ("vim", "updates vim history's files")
        ("all", "updates all history's files")
    ;
}
