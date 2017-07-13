#include "luna_lua.hpp"

int lunaL::size(lua_State *L) {
    int w = luaL_checkinteger(L, 1);
    int h = luaL_checkinteger(L, 2);
    const char* t = luaL_checkstring(L, 3);

    // Set global width and height
    lua_pushinteger(L, w);
    lua_setglobal(L, "width");
    lua_pushinteger(L, h);
    lua_setglobal(L, "height");

    Sketch::instance()->createWindow(w, h, t);
    return 0;
}

int lunaL::clear(lua_State *L) {
    Sketch::instance()->getWindow().clear();    
    return 0;
}

int lunaL::color(lua_State *L) {
    int lcolor = luaL_checkinteger(L, 1);
    sf::Color newColor;

    switch(lcolor) {
        case 0: newColor = sf::Color::Black;        break;
        case 1: newColor = sf::Color::White;        break;
        case 2: newColor = sf::Color::Red;          break;
        case 3: newColor = sf::Color::Green;        break;
        case 4: newColor = sf::Color::Blue;         break;
        case 5: newColor = sf::Color::Yellow;       break;
        case 6: newColor = sf::Color::Magenta;      break;
        case 7: newColor = sf::Color::Cyan;         break;
        case 8: newColor = sf::Color::Transparent;  break;
        default: newColor = sf::Color::White;       break;
    }

    Sketch::instance()->setColor(newColor);
    return 0;
}

int lunaL::text(lua_State *L) {
    const char* str = luaL_checkstring(L, 1);
    int size = luaL_checkinteger(L, 2);
    float posx = luaL_checknumber(L, 3);
    float posy = luaL_checknumber(L, 4);

    Sketch::instance()->text(str, size, posx, posy);
    return 0;
}

int lunaL::rect(lua_State *L) {
    float x1 = luaL_checknumber(L, 1);
    float y1 = luaL_checknumber(L, 2);
    float x2 = luaL_checknumber(L, 3);
    float y2 = luaL_checknumber(L, 4);

    sf::Vector2f p1(x1, y1);
    sf::Vector2f p2(x2, y2);

    Sketch::instance()->rect(p1, p2);
    return 0;
}

int lunaL::line(lua_State *L) {
    float x1 = luaL_checknumber(L, 1);
    float y1 = luaL_checknumber(L, 2);
    float x2 = luaL_checknumber(L, 3);
    float y2 = luaL_checknumber(L, 4);

    sf::Vector2f p1(x1, y1);
    sf::Vector2f p2(x2, y2);

    Sketch::instance()->line(p1, p2);
    return 0;  
}

int lunaL::circ(lua_State *L) {
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float r = luaL_checknumber(L, 3);

    sf::Vector2f pos(x, y);

    Sketch::instance()->circ(pos, r);
    return 0;
}