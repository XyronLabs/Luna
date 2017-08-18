#pragma once

#include <map>
#include <string>

class Configuration {
    std::map<std::string, std::string> configData;

public:
    Configuration(std::string configFilePath);
    
    std::string get(std::string key);
    void set(std::string key, std::string value);
    bool exists(std::string key);
};