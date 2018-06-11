#include "luna/Sketch.hpp"
#include "luna/luna_lua.hpp"
#include "luna/Logger.hpp"
#include "luna/Defines.hpp"
#include "luna/LunaConf.hpp"

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
    registerLunaFunction(setLogLevel);
    registerLunaFunction(frameRate);
    registerLunaFunction(exit);
    registerLunaFunction(icon);
    registerLunaFunction(noLoop);
    registerLunaFunction(setMouseVisible);
}

bool Sketch::preload(const char* lua_main, const std::vector<const char*>& lua_args) {

    /* Load Lua libraries */
    luaL_loadfile(L, getLunaResource("lua/modules.lua"));
    if (lua_pcall(L, 0, 0, 0)) {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("module_load_error") });
        return true;
    }

    // Set default values to variables
    default_font.loadFromFile(getLunaResource( luna_conf::main.get("default_font") ));
    current_color = sf::Color::White;

    // Load lua/main.lua
    if (!luaL_loadfile(L, lua_main ? lua_main : "main.luna")) {
        for (const char* arg : lua_args)
            lua_pushstring(L, arg);

        if (lua_pcall(L, lua_args.size(), 0, 0)) {
            Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("main_lua_error") }, L);
            return true;
        }
    } else {
        Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("main_lua_not_found") }, L);
        if (!luaL_loadfile(L, getLunaResource("lua/noapp.luna"))) {
            lua_pcall(L, 0, 0, 0);
        } else {
            Logger::instance().log(Logger::Level::DEBUG, { "Luna resource noapp.lua not found!" });
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

    lua_pushinteger(L, 0);
    lua_setglobal(L, "mouseX");
    lua_pushinteger(L, 0);
    lua_setglobal(L, "mouseY");

    return false;
}

void Sketch::loop() {
    // Main loop
    while (window->isOpen()) {
        sf::Event ev;
        while(window->pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window->close();
            } else if (isRunning) {
                handleEvent(ev);
            }
        }

        // Run loop only if not paused
        if (isRunning) {
            lua_getglobal(L, "render");
            if (lua_pcall(L, 0, 0, 0)) {
                Logger::instance().log(Logger::Level::FATAL, { luna_conf::lang.get("render_function_error") }, L);
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

    for (auto& t : shapeCache)
        delete t.second;

    for (auto& t : textureCache)
        delete t.second;

    for (auto& t : soundCache) {
        delete t.second->getBuffer();
        delete t.second;
    }

    for (auto& t : textCache)
        delete t.second;

    for (auto& t : tmpVertex)
        delete t.second;
}

void Sketch::handleEvent(const sf::Event& ev) {
    if (!lua_getglobal(L, "input")) {
        return;
    }

    lua_newtable(L);

    switch(ev.type) {
        case sf::Event::KeyPressed:
            lua_addvalue_s_s(L, "type", "key_pressed");
            lua_addvalue_s_i(L, "key", ev.key.code);
            break;

        case sf::Event::KeyReleased:
            lua_addvalue_s_s(L, "type", "key_released");
            lua_addvalue_s_i(L, "key", ev.key.code);
            break;

        case sf::Event::TextEntered:
            lua_addvalue_s_s(L, "type", "text_entered");
            lua_addvalue_s_i(L, "character", ev.text.unicode);
            break;


        case sf::Event::MouseButtonPressed:
            lua_addvalue_s_s(L, "type", "mouse_button_pressed");
            lua_addvalue_s_i(L, "button", ev.mouseButton.button);
            break;

        case sf::Event::MouseButtonReleased:
            lua_addvalue_s_s(L, "type", "mouse_button_released");
            lua_addvalue_s_i(L, "button", ev.mouseButton.button);
            break;

        case sf::Event::MouseMoved: {
            sf::Vector2i pos = sf::Mouse::getPosition(*window);
            lua_addvalue_s_s(L, "type", "mouse_moved");
            lua_addvalue_s_i(L, "x", pos.x);
            lua_addvalue_s_i(L, "y", pos.y);
            break;
        }

        case sf::Event::MouseWheelScrolled:
            lua_addvalue_s_s(L, "type", "mouse_wheel_scrolled");
            lua_addvalue_s_s(L, "direction", ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel ? "vertical" : "horizontal");
            lua_addvalue_s_i(L, "delta", ev.mouseWheel.delta);
            break;

        case sf::Event::JoystickButtonPressed:
            lua_addvalue_s_s(L, "type", "joystick_button_pressed");
            lua_addvalue_s_i(L, "id", ev.joystickButton.joystickId);
            lua_addvalue_s_i(L, "button", ev.joystickButton.button);
            break;

        case sf::Event::JoystickButtonReleased:
            lua_addvalue_s_s(L, "type", "joystick_button_released");
            lua_addvalue_s_i(L, "id", ev.joystickButton.joystickId);
            lua_addvalue_s_i(L, "button", ev.joystickButton.button);
            break;

        case sf::Event::JoystickMoved:
            lua_addvalue_s_s(L, "type", "joystick_moved");
            lua_addvalue_s_i(L, "id", ev.joystickMove.joystickId);
            lua_addvalue_s_i(L, "axis", ev.joystickMove.axis);
            lua_addvalue_s_n(L, "position", ev.joystickMove.position);
            break;

        case sf::Event::JoystickConnected:
            lua_addvalue_s_s(L, "type", "joystick_connected");
            lua_addvalue_s_i(L, "id", ev.joystickConnect.joystickId);
            break;

        case sf::Event::JoystickDisconnected:
            lua_addvalue_s_s(L, "type", "joystick_disconnected");
            lua_addvalue_s_i(L, "id", ev.joystickConnect.joystickId);
            break;

        case sf::Event::LostFocus:
            lua_addvalue_s_s(L, "type", "focus_lost");
            break;

        case sf::Event::GainedFocus:
            lua_addvalue_s_s(L, "type", "focus_gained");
            break;

        case sf::Event::Resized:
            lua_addvalue_s_s(L, "type", "resized");
            lua_addvalue_s_i(L, "width", ev.size.width);
            lua_addvalue_s_i(L, "height", ev.size.height);
            break;

        default:
            lua_addvalue_s_s(L, "type", "unknown");
            break;
    }

    lua_pcall(L, 1, 0, 0);
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
std::map<std::string, sf::Shape*>& Sketch::getShapeCache() {
    return shapeCache;
}

std::map<std::string, sf::Texture*>& Sketch::getTextureCache() {
    return textureCache;
}

std::map<std::string, sf::Sound*>& Sketch::getSoundCache() {
    return soundCache;
}

std::map<std::string, sf::Text*>& Sketch::getTextCache() {
    return textCache;
}

sf::RenderWindow& Sketch::getWindow() {
    return *window;
}

const sf::Font& Sketch::getDefaultFont() const {
    return default_font;
}

const sf::Color& Sketch::getCurrentColor() const {
    return current_color;
}

/*
    Setters
*/
void Sketch::setColor(sf::Color newColor) {
    this->current_color = newColor;
}