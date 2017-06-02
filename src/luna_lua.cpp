#include "luna_lua.hpp"

int lunaL::size(lua_State *L) {
    int w = luaL_checkinteger(L, 1);
    int h = luaL_checkinteger(L, 2);
    const char* t = luaL_checkstring(L, 3);

    Sketch::instance()->createWindow(w, h, t);

    return 0;
}

int lunaL::text(lua_State *L) {
    const char* str = luaL_checkstring(L, 1);
    int size = luaL_checkinteger(L, 2);

    Sketch::instance()->text(str, size);

    return 0;
}