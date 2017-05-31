#include <SFML/Graphics.hpp>
#include <lua.hpp>

sf::RenderWindow *w;

int main() {
    lua_State *L = luaL_newstate();
    w = new sf::RenderWindow(sf::VideoMode(1280,720), "Luna");

    while (w->isOpen()) {
        sf::Event ev;
        while(w->pollEvent(ev)) {
            switch(ev.type) {
                case sf::Event::Closed:
                    w->close();
            }
        }

    }

    lua_close(L);
    delete w;
}