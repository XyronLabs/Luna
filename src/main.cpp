#include <memory>

#include <SFML/Graphics.hpp>
#include <lua.hpp>

std::unique_ptr<sf::RenderWindow> window;

int main() {
    lua_State *L = luaL_newstate();

    // Load lua/main.lua
    luaL_openlibs(L);
    luaL_loadfile(L, "lua/main.lua");
    lua_pcall(L, 0, 0, 0);

    lua_getglobal(L, "setup");
    lua_pcall(L, 0, 0, 0);

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280,720), "Luna");

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


    lua_close(L);
}