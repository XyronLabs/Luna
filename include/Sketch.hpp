#pragma once

#include <SFML/Graphics.hpp>
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
        Sketch instance for singleton
    */
    static Sketch *s_instance;

    /*
        Private constructor for singleton
        All Lua functions and libraries are
        loaded here
    */
    Sketch();
    
public:

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
        Return Sketch instance, singleton
    */
    static Sketch* instance();

    /*
        Called by size(w,h,t) Lua function
        Set any settings needed for the window here
        (VSync, Antialiasing, etc)
    */
    void createWindow(int width, int height, const char* title);

    /*
        Return window reference, used in luna_lua functions
    */
    sf::RenderWindow& getWindow();

    /*
        Set value of 'current_color', called
        from color(c) Lua function
    */
    void setColor(sf::Color newColor);

    /*
        Draw a string of text on the screen, called
        from text(t,s) Lua function
    */
    void text(const char* str, int size);

    /*
        Draw a rectangle starting at point 'p1',
        with width and height 'p2', called from
        rect(x1,y1,x2,y2) Lua function 
    */
    void rect(sf::Vector2f p1, sf::Vector2f p2);

    /*
        Draw a line between points 'p1' and 'p2',
        called from line(x1,y1,x2,y2) Lua function 
    */
    void line(sf::Vector2f p1, sf::Vector2f p2);

    /*
        Draw a circle with center at point 'pos'
        and radius 'r', called from
        circ(x,y,r) Lua function
    */
    void circ(sf::Vector2f pos, float r);
};

