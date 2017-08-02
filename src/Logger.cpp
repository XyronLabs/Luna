#include "Logger.hpp"

Logger::Logger()
    : logLevel(Logger::Level::WARNING) {
}

Logger& Logger::instance() {
    static Logger s_instance;
    return s_instance;
}

void Logger::setLevel(Level level) {
    logLevel = level;
}

void Logger::logFatal(const char* msg, lua_State *L) {
    if (logLevel >= Logger::Level::FATAL) {
        std::cout << "[FATAL] " << msg;
        if (L) std::cout << " || Lua output: " << luaL_checkstring(L, -1);
        std::cout << std::endl;
    }
}
void Logger::logError(const char* msg, lua_State *L) {
    if (logLevel >= Logger::Level::ERROR) {
        std::cout << "[ERROR] " << msg;
        if (L) std::cout << " || Lua output: " << luaL_checkstring(L, -1);
        std::cout << std::endl;
    }
}
void Logger::logWarning(const char* msg, lua_State *L) {
    if (logLevel >= Logger::Level::WARNING) {
        std::cout << "[WARNING] " << msg;
        if (L) std::cout << " || Lua output: " << luaL_checkstring(L, -1);
        std::cout << std::endl;
    }
}
void Logger::logInfo(const char* msg, lua_State *L) {
    if (logLevel >= Logger::Level::INFO) {
        std::cout << "[INFO] " << msg;
        if (L) std::cout << " || Lua output: " << luaL_checkstring(L, -1);
        std::cout << std::endl;
    }
}
void Logger::logDebug(const char* msg, lua_State *L) {
    if (logLevel >= Logger::Level::DEBUG) {
        std::cout << "[DEBUG] " << msg;
        if (L) std::cout << " || Lua output: " << luaL_checkstring(L, -1);
        std::cout << std::endl;
    }
}