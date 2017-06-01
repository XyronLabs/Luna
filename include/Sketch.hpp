#pragma once

#include <SFML/Graphics.hpp>
#include <lua.hpp>

class Sketch {
    std::unique_ptr<sf::RenderWindow> window;
    lua_State *L;
    
public:
    Sketch();
    ~Sketch();

    void setup();
    void loop();
};