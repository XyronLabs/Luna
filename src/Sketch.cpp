#include "Sketch.hpp"
#include "luna_lua.hpp"
#include "Logger.hpp"
#include "Defines.hpp"

Sketch& Sketch::instance() {
    static Sketch s_instance;
    return s_instance;
}

Sketch::Sketch() {
    L = luaL_newstate();
    luaL_openlibs(L);

    /* Register Lua functions */
    registerLunaFunction(size);
    registerLunaFunction(clear);
    registerLunaFunction(color);
    registerLunaFunction(text);
    registerLunaFunction(rect);
    registerLunaFunction(line);
    registerLunaFunction(ellipse);
    
    registerLunaFunction(registerObject);
    registerLunaFunction(editObject);
    registerLunaFunction(renderObject);
    registerLunaFunction(removeObject);
    
    registerLunaFunction(log);
    registerLunaFunction(frameRate);
    registerLunaFunction(exit);

    /* Load Lua libraries */
    luaL_loadfile(L, getLunaResource("lua/modules.lua"));
    if (lua_pcall(L, 0, 0, 0)) {
        Logger::instance().log(Logger::Level::FATAL, {"Error loading Lua modules"});
    }
}

bool Sketch::preload(const char* lua_main) {
    // Set default values to variables
    default_font.loadFromFile(getLunaResource("font/Roboto-Regular.ttf"));
    current_color = sf::Color::White;

    // Load lua/main.lua
    luaL_loadfile(L, lua_main ? lua_main : "main.lua");
    if (lua_pcall(L, 0, 0, 0)) {
        Logger::instance().log(Logger::Level::FATAL, {"Main.lua was not found!"}, L);
        return true;
    }

    return false;
}

bool Sketch::setup() {
    // Call Lua setup function, exit if not found
    lua_getglobal(L, "setup");
    if (lua_pcall(L, 0, 0, 0)) {
        Logger::instance().log(Logger::Level::FATAL, {"Setup function not found!"}, L);
        return true;
    }

    // Exit if 'size' is not called
    if (!window) {
        Logger::instance().log(Logger::Level::FATAL, {"Window was not created, use size(width, height, title)"});
        return true;
    }

    return false;
}

void Sketch::loop() {
    // Cleanup and exit if render function is not found
    if (!lua_getglobal(L, "render")) {
        Logger::instance().log(Logger::Level::FATAL, {"Render function not found!"});
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

                // Set mousekeys[X] true
                case sf::Event::MouseButtonPressed:
                    lua_getglobal(L, "pressMouseKey");
                    lua_pushinteger(L, ev.mouseButton.button);
                    lua_pcall(L, 1, 0, 0);
                    break;

                // Set mousekeys[X] false
                case sf::Event::MouseButtonReleased:
                    lua_getglobal(L, "releaseMouseKey");
                    lua_pushinteger(L, ev.mouseButton.button);
                    lua_pcall(L, 1, 0, 0);
                    break;

                case sf::Event::MouseMoved: {
                    sf::Vector2i pos = sf::Mouse::getPosition(*window);
                    lua_pushinteger(L, pos.x);
                    lua_setglobal(L, "mouseX");
                    lua_pushinteger(L, pos.y);
                    lua_setglobal(L, "mouseY");
                    break;
                }

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
    
    for (auto& t : textureCache) {
        Logger::instance().log(Logger::Level::DEBUG, {"Deleting texture"});
        delete t.second;
    }

    for (auto& t : soundCache) {
        Logger::instance().log(Logger::Level::DEBUG, {"Deleting sound"});
        delete t.second->getBuffer();
    }
}

void Sketch::createWindow(int width, int height, const char* title) {
    sf::ContextSettings s;
    s.antialiasingLevel = 8;

    // Only create window the first time size(w,h,t) is called
    if (!window)
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Default, s);
    window->setFramerateLimit(60);
}

/*
    Getters
*/
std::map<std::string, std::unique_ptr<sf::Shape>>& Sketch::getShapeCache() {
    return shapeCache;
}

std::map<std::string, sf::Texture*>& Sketch::getTextureCache() {
    return textureCache;
}

std::map<std::string, std::unique_ptr<sf::Sound>>& Sketch::getSoundCache() {
    return soundCache;
}

std::map<std::string, std::unique_ptr<sf::Text>>& Sketch::getTextCache() {
    return textCache;
}

sf::RenderWindow& Sketch::getWindow() {
    return *window;
}

sf::Font& Sketch::getDefaultFont() {
    return default_font;
}

sf::Color& Sketch::getCurrentColor() {
    return current_color;
}

/*
    Setters
*/
void Sketch::setColor(sf::Color newColor) {
    this->current_color = newColor;
}