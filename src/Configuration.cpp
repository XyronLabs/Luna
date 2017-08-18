#include "Configuration.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

Configuration::Configuration(std::string configFilePath)
    : filePath (configFilePath) 
{
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

void Configuration::save(std::string key) {
    // Read file
    std::vector<std::string> lines;
    std::string curr;
    std::ifstream filei(filePath);

    while(std::getline(filei, curr))
        lines.push_back(curr);
    filei.close();

    // Write new config
    std::ofstream file(filePath);
    bool found = false;

    for (std::string line : lines) {
        if (line.find(key) != std::string::npos) {
            line = key + "=" + configData[key];
            found = true;
        }
        file << line << std::endl;
    }

    // If it is a new config, append to the end of the file
    if (!found) {
        file << key + "=" + configData[key] << std::endl;
    }

    file.close();
}

std::ostream& operator<<(std::ostream& os, const Configuration& conf) {
    for (const auto& pair : conf.configData)
        os << pair.first << " = " << pair.second << std::endl;
    return os;
}