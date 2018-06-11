#pragma once

#define lua_addvalue_s_s(luaState, key, value) \
            lua_pushstring(luaState, key); \
            lua_pushstring(luaState, value); \
            lua_settable(luaState, -3)

#define lua_addvalue_s_i(luaState, key, value) \
            lua_pushstring(luaState, key); \
            lua_pushinteger(luaState, value); \
            lua_settable(luaState, -3)

#define lua_addvalue_s_n(luaState, key, value) \
            lua_pushstring(luaState, key); \
            lua_pushnumber(luaState, value); \
            lua_settable(luaState, -3)