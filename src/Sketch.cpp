#include "Sketch.hpp"
#include "luna_lua.hpp"
#include "Logger.hpp"
#include "Defines.hpp"
#include "LunaConf.hpp"

Sketch& Sketch::instance() {
    static Sketch s_instance;
    return s_instance;
}

Sketch::Sketch() {
    isRunning = true;

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
    registerLunaFunction(icon);
    registerLunaFunction(noLoop);

    /* Load Lua libraries */
    luaL_loadfile(L, getLunaResource("lua/modules.lua"));
    if (lua_pcall(L, 0, 0, 0)) {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("module_load_error") });
    }
}

bool Sketch::preload(const char* lua_main, const char* lua_args) {
    // Set default values to variables
    default_font.loadFromFile(getLunaResource( luna_conf::main.get("default_font") ));
    current_color = sf::Color::White;

    // Load lua/main.lua
    if (!luaL_loadfile(L, lua_main ? lua_main : "main.luna")) {
        if (lua_args)
            lua_pushstring(L, lua_args);
            
        if (lua_pcall(L, lua_args ? 1 : 0, 0, 0)) {
            Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("main_lua_error") }, L);
            return true;
        }
    } else {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("main_lua_not_found") }, L);
        if (!luaL_loadfile(L, getLunaResource("lua/noapp.luna"))) {
            lua_pcall(L, 0, 0, 0);
        } else {
#ifdef LUNA_DEBUG
            Logger::instance().log(Logger::Level::DEBUG, { "Luna resource noapp.lua not found!" });
#endif
            return true;
        }
    }
    
    return false;
}

bool Sketch::setup() {

    if (!lua_getglobal(L, "setup")) {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("setup_function_not_found") });
        return true;
    }
    if (!lua_getglobal(L, "render")) {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("render_function_not_found") });
        return true;
    }

    lua_getglobal(L, "setup");
    if (lua_pcall(L, 0, 0, 0)) {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("setup_function_error") }, L);
        return true;
    }


    // Exit if 'size' is not called
    if (!window) {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("window_not_created") });
        return true;
    }

    return false;
}

void Sketch::loop() {
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

        // Run loop only if not paused
        if (isRunning) {

            // Call Lua render function
            lua_getglobal(L, "render");
            if (lua_pcall(L, 0, 0, 0)) {
                Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("render_function_error") }, L);
                window->close();
                return;
            }

            // Call Lua input function if it exists
            if (lua_getglobal(L, "input"))
                if (lua_pcall(L, 0, 0, 0)) {
                    Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("input_function_error") }, L);
                    window->close();
                    return;
                }

        }

        // Show the new frame
        window->display();
    }
}

void Sketch::cleanup() {
    lua_close(L);
    
    for (auto& t : textureCache) {
#ifdef LUNA_DEBUG
        Logger::instance().log(Logger::Level::DEBUG, {"Deleting texture"});
#endif
        delete t.second;
    }

    for (auto& t : soundCache) {
#ifdef LUNA_DEBUG
        Logger::instance().log(Logger::Level::DEBUG, {"Deleting sound"});
#endif
        delete t.second->getBuffer();
    }
}

void Sketch::createWindow(int width, int height, const char* title) {
    sf::ContextSettings s;
    s.antialiasingLevel = atoi(luna_conf::main.get("antialiasing_level").c_str());
    int mode = sf::Style::Default;

    // Enable fullscreen mode
    if (width == 0 && height == 0) {
        width = sf::VideoMode::getDesktopMode().width;
        height = sf::VideoMode::getDesktopMode().height;
        mode = sf::Style::Fullscreen;
    }

    // Only create window the first time size(w,h,t) is called
    if (!window)
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, mode, s);
            
    // Set global width and height
    lua_pushinteger(L, width);
    lua_setglobal(L, "width");
    lua_pushinteger(L, height);
    lua_setglobal(L, "height");

    sf::Image icon;
    icon.loadFromFile(getLunaResource("logo_small.png"));
    window->setIcon(256, 256, icon.getPixelsPtr());
    window->setFramerateLimit(60);
}

/*
    Stop calling render and input functions
*/
void Sketch::noLoop() {
    isRunning = false;
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