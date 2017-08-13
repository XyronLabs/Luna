#pragma once

#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
#include <lua5.3/lua.hpp>

class Logger {
public:
    /*
        Log levels
    */
    enum Level { FATAL, ERROR, WARNING, INFO, DEBUG};

private:
    /*
        Current log level
    */
    Level logLevel;

    
    std::vector<std::string> printableLevels = { "FATAL", "ERROR", "WARNING", "INFO", "DEBUG" };

private:
    /*
        Private constructor for singleton
    */
    Logger();

public:
    /*
        Return Logger instance, singleton
    */
    static Logger& instance();

    void setLevel(Level level);

    void log(Level desiredLogLevel, const std::initializer_list<std::string>& msg, lua_State *L = nullptr);

};