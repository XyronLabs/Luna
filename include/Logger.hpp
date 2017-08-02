#pragma once

#include <iostream>
#include <lua5.3/lua.hpp>

class Logger {
public:
    /*
        Log levels
    */
    enum Level { FATAL, ERROR, WARNING, INFO, DEBUG };

private:
    /*
        Current log level
    */
    Level logLevel;

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

    void logFatal(const char* msg, lua_State *L = nullptr);
    void logError(const char* msg, lua_State *L = nullptr);
    void logWarning(const char* msg, lua_State *L = nullptr);
    void logInfo(const char* msg, lua_State *L = nullptr);
    void logDebug(const char* msg, lua_State *L = nullptr);

};