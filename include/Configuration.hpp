#pragma once

#include <map>
#include <string>

class Configuration {
    std::map<std::string, std::string> configData;

public:
    Configuration(std::string configFilePath);
    
    std::string get(std::string key);
    bool set(std::string key, std::string value);
};