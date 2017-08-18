#include "Configuration.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

Configuration::Configuration(std::string configFilePath) {
    std::ifstream file;
    file.open(configFilePath, std::ifstream::in);

    std::string line, key;
    
    while (std::getline(file, line)) {
        if (line[0] == '#') continue;
        std::istringstream currLine(line);

        if (std::getline(currLine, key, '='))
            std::getline(currLine, configData[key]);
    }

    file.close();
}

std::string Configuration::get(std::string key) {
    return configData[key];
}

void Configuration::set(std::string key, std::string value) {
    configData[key] = value;
}

bool Configuration::exists(std::string key) {
    return configData[key] != "";
}

void Configuration::print() {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const Configuration& conf) {
    for (const auto& pair : conf.configData)
        os << pair.first << " = " << pair.second << std::endl;
    return os;
}