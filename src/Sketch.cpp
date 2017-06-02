#include <iostream>
#include "Sketch.hpp"
#include "luna_lua.hpp"

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

    /* Register lua functions */
    lua_register(L, "size", lunaL::size);
    lua_register(L, "text", lunaL::text);

}

bool Sketch::preload(const char* lua_main) {
    default_font.loadFromFile("res/font/Roboto-Regular.ttf");

    // Load lua/main.lua
    luaL_loadfile(L, lua_main ? lua_main : "lua/main.lua");
    if (lua_pcall(L, 0, 0, 0)) {
        std::cerr << "Error loading main script!" << std::endl;
        return true;
    }

    return false;
}

bool Sketch::setup() {
    lua_getglobal(L, "setup");
    if (lua_pcall(L, 0, 0, 0)) {
        std::cerr << "Error: Setup function not found!" << std::endl;
        return true;
    }

    // Create a default window if 'size' is not called
    if (!window) {
        std::cerr << "Error: Window was not created, use size(width, height, title)" << std::endl;
        return true;
    }

    return false;
}

void Sketch::loop() {
    // Cleanup and exit if render function is not found
    if (!lua_getglobal(L, "render")) {
        std::cerr << "Render function not found!" << std::endl;
        return;
    }

    while (window->isOpen()) {
        sf::Event ev;
        while(window->pollEvent(ev)) {
            switch(ev.type) {
                case sf::Event::Closed:
                    window->close();
            }
        }

        window->clear();

        lua_getglobal(L, "render");
        lua_pcall(L, 0, 0, 0);

        window->display();
    }

}

void Sketch::cleanup() {
    lua_close(L);
}

void Sketch::createWindow(int width, int height, const char* title) {
    if (!window)
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
}


void Sketch::text(const char* str, int size) {
    sf::Text t;
    t.setString(str);
    t.setFont(default_font);
    t.setCharacterSize(size);

    window->draw(t);
}