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

int lunaL::rect(lua_State *L) {
    int x1 = luaL_checkinteger(L, 1);
    int y1 = luaL_checkinteger(L, 2);
    int x2 = luaL_checkinteger(L, 3);
    int y2 = luaL_checkinteger(L, 4);

    sf::Vector2f p1(x1, y1);
    sf::Vector2f p2(x2, y2);

    Sketch::instance()->rect(p1, p2);

    return 0;
}