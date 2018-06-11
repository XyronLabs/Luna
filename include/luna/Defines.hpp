#pragma once

#define LUNA_VERSION "0.9-17"

#ifdef LUNA_STANDALONE
#define RES_PATH "res/"
#elif (defined LUNA_DEBUG)
#define RES_PATH "resources/luna/"
#elif (defined _WIN32 || defined _WIN64)
#define RES_PATH "C:/Program Files (x86)/XyronLabs/Luna/res/"
#elif (defined LINUX || defined __linux__)
#define RES_PATH "/usr/local/luna/res/"
#elif (defined __APPLE || defined __MACH__)
#define RES_PATH "res/"
#endif

#define getLunaResource(path) (std::string(RES_PATH) + path).c_str()

#define registerLunaFunction(func)  lua_register(L, #func, lunaL::func)

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