#pragma once

#define LUNA_VERSION "0.7-12"

#ifdef LUNA_DEBUG
#define RES_PATH "res/"
#elif LUNA_STANDALONE
#define RES_PATH ".luna_bin/res/"
#elif _WIN32
#define RES_PATH "C:/Program Files (x86)/XyronLabs/Luna/res/"
#else // Asume linux
#define RES_PATH "/usr/local/luna/res/"
#endif

#define getLunaResource(path) (std::string(RES_PATH) + path).c_str()

#define registerLunaFunction(func)  lua_register(L, #func, lunaL::func)