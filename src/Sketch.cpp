#include "Sketch.hpp"

// Allocate pointer, not the object
Sketch *Sketch::s_instance = 0;
Sketch* Sketch::instance() {
    if(!s_instance)
        s_instance = new Sketch;
    return s_instance;
}

Sketch::Sketch() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280,720), "Luna");
    
    L = luaL_newstate();
    luaL_openlibs(L);
}

bool Sketch::preload(const char* lua_main) {
    // Load lua/main.lua
    luaL_loadfile(L, lua_main ? lua_main : "lua/main.lua");
    lua_pcall(L, 0, 0, 0);
}

void Sketch::setup() {
    lua_getglobal(L, "setup");
    lua_pcall(L, 0, 0, 0);
}

void Sketch::loop() {
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