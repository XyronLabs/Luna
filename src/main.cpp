#include <memory>

#include <SFML/Graphics.hpp>
#include <lua.hpp>

std::unique_ptr<sf::RenderWindow> window;

int main() {
    lua_State *L = luaL_newstate();
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
        window->display();

    }


    lua_close(L);
}