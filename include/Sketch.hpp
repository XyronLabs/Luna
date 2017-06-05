#pragma once

#include <SFML/Graphics.hpp>
#include <lua.hpp>

class Sketch {
    std::unique_ptr<sf::RenderWindow> window;
    lua_State *L;

    sf::Font default_font;
    sf::Color current_color;

    static Sketch *s_instance;
    Sketch();
    
public:

    bool preload(const char* lua_main);
    bool setup();
    void loop();
    void cleanup();

    static Sketch* instance();

    void createWindow(int width, int height, const char* title);
    void setColor(sf::Color newColor);
    void text(const char* str, int size);
    void rect(sf::Vector2f p1, sf::Vector2f p2);
    void circ(sf::Vector2f pos, float r);
};

