#pragma once
#include <lua.hpp>
#include "Sketch.hpp"

// For defining Lua functions
typedef int(*lua_CFunction) (lua_State *L);

// All Luna Lua functions here
namespace lunaL {

    /* Set size and title of the window */
    int size(lua_State *L);

    /* Render a string of text */
    int text(lua_State *L);

    /* Render a rectangle */
    int rect(lua_State *L);

};