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

}

bool Sketch::preload(const char* lua_main) {
    // Load lua/main.lua
    luaL_loadfile(L, lua_main ? lua_main : "lua/main.lua");
    lua_pcall(L, 0, 0, 0);
}

void Sketch::setup() {
    lua_getglobal(L, "setup");
    lua_pcall(L, 0, 0, 0);

    // Create a default window if 'size' is not called
    if (!window)
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 600), "Luna");
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

void Sketch::createWindow(int width, int height, const char* title) {
    if (!window)
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
}