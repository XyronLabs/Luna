#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <lua5.3/lua.hpp>

/**
    Main Luna class, this class manages
    everything drawn on the screen
*/
class Sketch {
    /*
        Window itself
    */
    std::unique_ptr<sf::RenderWindow> window;

    /*
        Lua handler used in all Luna Lua functions
    */
    lua_State *L;

    /*
        Default font for text() Lua function
    */
    sf::Font default_font;

    /*
        Current color for drawing, can be
        changed with color() Lua function
    */
    sf::Color current_color;

    /*
        Caches for Lua objects
    */
    std::map<std::string, std::unique_ptr<sf::Shape>> shapeCache;
    std::map<std::string, sf::Texture*> textureCache;
    std::map<std::string, std::unique_ptr<sf::Sound>> soundCache;
    std::map<std::string, std::unique_ptr<sf::Text>> textCache;

    /*
        Private constructor for singleton
        All Lua functions and libraries are
        loaded here
    */
    Sketch();
    
public:
    /*
        Return Sketch instance, singleton
    */
    static Sketch& instance();
    
    /*
        Load the main Lua script and default vars
        (default font, color, etc)
    */
    bool preload(const char* lua_main);

    /*
        setup() Lua function, size(w,h,t) must be
        called in this function

        Exceptions: Setup function not found
                    Size Lua function is not called
    */
    bool setup();

    /*
        render() Lua function, called once per frame
        SFML events are handled here

        Exception: Render function not found
    */
    void loop();

    /*
        Any cleanup needed before exiting the program
    */
    void cleanup();

    /*
        Called by size(w,h,t) Lua function
        Set any settings needed for the window here
        (VSync, Antialiasing, etc)
    */
    void createWindow(int width, int height, const char* title);

    /*
        Getters
    */
    std::map<std::string, std::unique_ptr<sf::Shape>>& getShapeCache();
    std::map<std::string, sf::Texture*>& getTextureCache();
    std::map<std::string, std::unique_ptr<sf::Sound>>& getSoundCache();
    std::map<std::string, std::unique_ptr<sf::Text>>& getTextCache();

    sf::RenderWindow& getWindow();
    sf::Font& getDefaultFont();
    sf::Color& getCurrentColor();

    /*
        Setters
    */
    void setColor(sf::Color newColor);
};

