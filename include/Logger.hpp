#pragma once

#include <iostream>
#include <lua.hpp>

/*
    Log a message to std::cout
*/
void log(const char* msg);

/*
    Log a message to std::cerr
*/
void logErr(const char* msg);

/*
    Used for Lua errors,
    Log a message to std::cerr
    and Lua error at -1
*/
void logErr(const char* msg, lua_State *L);