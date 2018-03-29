#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <lua/lua.hpp>

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
    std::map<std::string, sf::Shape*> shapeCache;
    std::map<std::string, sf::Texture*> textureCache;
    std::map<std::string, sf::Sound*> soundCache;
    std::map<std::string, sf::Text*> textCache;
    std::map<std::string, sf::ConvexShape*> tmpVertex;

    /*
        Stop loop if noLoop is called
    */
    bool isRunning;

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
    bool preload(const char* lua_main, const std::vector<const char*>& lua_args);

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
        Stop calling render and input functions
    */
    void noLoop();

    /*
        Getters
    */
    std::map<std::string, sf::Shape*>& getShapeCache();
    std::map<std::string, sf::Texture*>& getTextureCache();
    std::map<std::string, sf::Sound*>& getSoundCache();
    std::map<std::string, sf::Text*>& getTextCache();

    sf::RenderWindow& getWindow();
    const sf::Font& getDefaultFont() const;
    const sf::Color& getCurrentColor() const;

    /*
        Setters
    */
    void setColor(sf::Color newColor);
};