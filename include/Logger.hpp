#pragma once
#include <iostream>
#include <lua.hpp>

void log(const char* msg);
void logErr(const char* msg);
void logErr(const char* msg, lua_State *L);