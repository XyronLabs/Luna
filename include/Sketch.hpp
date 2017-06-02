#pragma once

#include <SFML/Graphics.hpp>
#include <lua.hpp>

class Sketch {
    std::unique_ptr<sf::RenderWindow> window;
    lua_State *L;

    sf::Font default_font;

    static Sketch *s_instance;
    Sketch();
    
public:

    bool preload(const char* lua_main);
    bool setup();
    void loop();
    void cleanup();

    static Sketch* instance();

    void createWindow(int width, int height, const char* title);
    void text(const char* str, int size);
};

