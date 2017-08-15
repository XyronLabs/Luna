#pragma once

#define LUNA_VERSION "0.6-10"

#ifdef LUNA_DEBUG
#define RES_PATH "res/"
#else
#define RES_PATH "/usr/local/luna/res/"
#endif

#define getLunaResource(path) (std::string(RES_PATH) + path).c_str()

#define registerLunaFunction(func)  lua_register(L, #func, lunaL::func)