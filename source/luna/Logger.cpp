#include "Logger.hpp"

Logger::Logger()
#ifdef LUNA_DEBUG
    : logLevel(Logger::Level::DEBUG)
#else
    : logLevel(Logger::Level::INFO)
#endif
{ }

Logger& Logger::instance() {
    static Logger s_instance;
    return s_instance;
}

void Logger::setLevel(Level level) {
    logLevel = level;
}

void Logger::log(Level desiredLogLevel, const std::initializer_list<std::string>& msg, lua_State *L) {
    if (logLevel >= desiredLogLevel) {
        std::cout << "[" << printableLevels[desiredLogLevel] << "] ";
        for (const auto& s : msg) std::cout << s;

        if (L) std::cout << " || Lua output: " << luaL_checkstring(L, -1);
        std::cout << std::endl;
    }
}