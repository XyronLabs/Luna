#pragma once

#include <map>
#include <string>

class Configuration {
    std::string filePath;
    std::map<std::string, std::string> configData;

public:
    Configuration(std::string configFilePath);
    
    std::string get(std::string key);
    void set(std::string key, std::string value);
    bool exists(std::string key);
    void print();
    void save(std::string key);
    void saveAll();

    friend std::ostream& operator<<(std::ostream& os, const Configuration& conf);
};