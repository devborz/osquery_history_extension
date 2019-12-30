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

std::shared_ptr<std::vector<Option>> Options::readOption(
                                        const bpo::variables_map& vm,
                                        unsigned int& ec) {
    std::string option_;
    std::shared_ptr<std::vector <Option>> enabledOptions(new
                                                        std::vector<Option>());
    if (vm.count("help")) {
        Option option = help;
        enabledOptions.get()->push_back(option);
    }
    else if (vm.count("all")) {
        Option option = all;
        enabledOptions.get()->push_back(option);
    }
    else {
        if (vm.count("filesystem")) {
            Option option = filesystem;
            enabledOptions.get()->push_back(option);
        }
        if (vm.count("bash")) {
            Option option = bash;
            enabledOptions.get()->push_back(option);
        }
        if (vm.count("vim")) {
            Option option = vim;
            enabledOptions.get()->push_back(option);
        }

    }

    if (enabledOptions.get()->empty()) {
        notifyOptionError(" ");
        ec = 1;
    }

    return enabledOptions;
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
