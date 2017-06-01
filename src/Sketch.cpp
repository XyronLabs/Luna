#include "Sketch.hpp"

Sketch::Sketch(const char* lua_main) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280,720), "Luna");
    
    L = luaL_newstate();
    // Load lua/main.lua
    luaL_openlibs(L);
    luaL_loadfile(L, lua_main ? lua_main : "lua/main.lua");
    lua_pcall(L, 0, 0, 0);
}

Sketch::~Sketch() {
    lua_close(L);
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