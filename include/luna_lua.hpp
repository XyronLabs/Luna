#pragma once

#include <lua5.3/lua.hpp>
#include "Sketch.hpp"

// For defining Lua functions
typedef int(*lua_CFunction) (lua_State *L);

// All Luna Lua functions here
namespace lunaL {
    /* Set size and title of the window */
    int size(lua_State *L);

     /* Clear the window */
    int clear(lua_State *L);

    /* Set fill color */
    int color(lua_State *L);

    /* Render a string of text */
    int text(lua_State *L);

    /* Render a rectangle */
    int rect(lua_State *L);

    /* Render a rectangle */
    int line(lua_State *L);

    /* Render a rectangle */
    int circ(lua_State *L);

    /*
     * Methods for handling shapeMap
     */
    int addShape(lua_State *L);
    int editShape(lua_State *L);
    int renderShape(lua_State *L);
    int removeShape(lua_State *L);

    int addSound(lua_State *L);
    int playSound(lua_State *L);
    int pauseSound(lua_State *L);
    int stopSound(lua_State *L);
};