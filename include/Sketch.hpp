#pragma once

#include <SFML/Graphics.hpp>
#include <lua.hpp>

class Sketch {
    std::unique_ptr<sf::RenderWindow> window;
    lua_State *L;

    static Sketch *s_instance;
    Sketch();
    
public:
    ~Sketch();

    void setup();
    void loop();

    static Sketch* instance();
};
