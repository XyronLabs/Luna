#include "Sketch.hpp"
#include "luna_lua.hpp"
#include "Logger.hpp"

// Allocate pointer, not the object
Sketch *Sketch::s_instance = 0;
Sketch* Sketch::instance() {
    if(!s_instance)
        s_instance = new Sketch;
    return s_instance;
}

Sketch::Sketch() {
    L = luaL_newstate();
    luaL_openlibs(L);

    /* Register Lua functions */
    lua_register(L, "size", lunaL::size);
    lua_register(L, "clear", lunaL::clear);
    lua_register(L, "color", lunaL::color);
    lua_register(L, "text", lunaL::text);
    lua_register(L, "rect", lunaL::rect);
    lua_register(L, "line", lunaL::line);
    lua_register(L, "circ", lunaL::circ);

    /* Load Lua libraries */
#ifdef LUNA_DEBUG
    luaL_loadfile(L, "res/lua/colors.lua");     lua_pcall(L, 0, 0, 0);
    luaL_loadfile(L, "res/lua/rectangle.lua");  lua_pcall(L, 0, 0, 0);
    luaL_loadfile(L, "res/lua/circle.lua");     lua_pcall(L, 0, 0, 0);
    luaL_loadfile(L, "res/lua/keys.lua");     lua_pcall(L, 0, 0, 0);
#else
    luaL_loadfile(L, "/usr/local/luna/res/lua/colors.lua");     lua_pcall(L, 0, 0, 0);
    luaL_loadfile(L, "/usr/local/luna/res/lua/rectangle.lua");  lua_pcall(L, 0, 0, 0);
    luaL_loadfile(L, "/usr/local/luna/res/lua/circle.lua");     lua_pcall(L, 0, 0, 0);
    luaL_loadfile(L, "/usr/local/luna/res/lua/keys.lua");     lua_pcall(L, 0, 0, 0);
#endif
}

bool Sketch::preload(const char* lua_main) {
    // Set default values to variables
#ifdef LUNA_DEBUG
    default_font.loadFromFile("res/font/Roboto-Regular.ttf");
#else
    default_font.loadFromFile("/usr/local/luna/res/font/Roboto-Regular.ttf");
#endif
    current_color = sf::Color::White;

    // Load lua/main.lua
    luaL_loadfile(L, lua_main ? lua_main : "main.lua");
    if (lua_pcall(L, 0, 0, 0)) {
        logErr("Error: Main.lua was not found!", L);
        return true;
    }

    return false;
}

bool Sketch::setup() {
    // Call Lua setup function, exit if not found
    lua_getglobal(L, "setup");
    if (lua_pcall(L, 0, 0, 0)) {
        logErr("Error: Setup function not found!", L);
        return true;
    }

    // Exit if 'size' is not called
    if (!window) {
        logErr("Error: Window was not created, use size(width, height, title)");
        return true;
    }

    return false;
}

void Sketch::loop() {
    // Cleanup and exit if render function is not found
    if (!lua_getglobal(L, "render")) {
        logErr("Render function not found!");
        return;
    }

    // Main loop
    while (window->isOpen()) {
        // Check if window has to close
        sf::Event ev;
        while(window->pollEvent(ev)) {
            switch(ev.type) {
                case sf::Event::Closed:
                    window->close();
                    break;

                // Set keys[X] true
                case sf::Event::KeyPressed:
                    lua_getglobal(L, "pressKey");
                    lua_pushinteger(L, ev.key.code);
                    lua_pcall(L, 1, 0, 0);
                    break;

                // Set keys[X] false
                case sf::Event::KeyReleased:
                    lua_getglobal(L, "releaseKey");
                    lua_pushinteger(L, ev.key.code);
                    lua_pcall(L, 1, 0, 0);
                    break;

                default:
                    break;
            }
        }

        // Call Lua render function
        lua_getglobal(L, "render");
        lua_pcall(L, 0, 0, 0);

        // Call Lua input function
        lua_getglobal(L, "input");
        lua_pcall(L, 0, 0, 0);

        // Show the new frame
        window->display();
    }

}

void Sketch::cleanup() {
    lua_close(L);
}

sf::RenderWindow& Sketch::getWindow() {
    return *window;
}

void Sketch::createWindow(int width, int height, const char* title) {
    sf::ContextSettings s;
    s.antialiasingLevel = 8;

    // Only create window the first time size(w,h,t) is called
    if (!window)
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Default, s);
    window->setVerticalSyncEnabled(true);
}

void Sketch::setColor(sf::Color newColor) {
    this->current_color = newColor;
}

void Sketch::text(const char* str, int size, float posx, float posy) {
    sf::Text t;
    t.setString(str);
    t.setFont(default_font);
    t.setCharacterSize(size);
    t.move(posx, posy);
    //t.setFillColor(current_color);

    window->draw(t);
}

void Sketch::rect(sf::Vector2f p1, sf::Vector2f p2) {
    sf::RectangleShape box(p2);
    box.move(p1.x, p1.y);
    box.setFillColor(current_color);

    window->draw(box);
}

void Sketch::line(sf::Vector2f p1, sf::Vector2f p2) {
    sf::Vertex line[] =
    {
        sf::Vertex(p1),
        sf::Vertex(p2)
    };

    window->draw(line, 2, sf::Lines);
}

void Sketch::circ(sf::Vector2f pos, float r) {
    sf::CircleShape circle(r);
    circle.move(pos.x, pos.y);
    circle.setFillColor(current_color);

    window->draw(circle);
}