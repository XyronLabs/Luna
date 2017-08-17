#include "Configuration.hpp"

#include <iostream>
#include <fstream>
#include <string>

Configuration::Configuration(std::string configFilePath) {
    std::ifstream file;
    file.open(configFilePath, std::ifstream::in);

    std::string key, value;
    
    while (file.good()) {
        std::getline(file, key, '=');
        std::getline(file, value);
        configData[key] = value;
        std::cout << key << ":" << configData[key] << std::endl;
    }

    file.close();
}