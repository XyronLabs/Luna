#include "Logger.hpp"

void log(const char* msg) {
    std::cout << msg << std::endl;
}

void logErr(const char* msg) {
    std::cerr << msg << std::endl;
}

void logErr(const char* msg, lua_State *L) {
    logErr(msg);
    std::cerr << "Lua output: " << luaL_checkstring(L, -1) << std::endl << std::endl;
}