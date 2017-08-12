#include "luna_lua.hpp"
#include "Logger.hpp"

int lunaL::size(lua_State *L) {
    int w = luaL_checkinteger(L, 1);
    int h = luaL_checkinteger(L, 2);
    const char* t = luaL_checkstring(L, 3);

    // Set global width and height
    lua_pushinteger(L, w);
    lua_setglobal(L, "width");
    lua_pushinteger(L, h);
    lua_setglobal(L, "height");

    Sketch::instance().createWindow(w, h, t);
    return 0;
}

int lunaL::clear(lua_State *L) {
    Sketch::instance().getWindow().clear();    
    return 0;
}

int lunaL::color(lua_State *L) {
    unsigned int newColor = luaL_checkinteger(L, 1);

    Sketch::instance().setColor(sf::Color(newColor));
    return 0;
}

int lunaL::text(lua_State *L) {
    const char* str = luaL_checkstring(L, 1);
    int size = luaL_checkinteger(L, 2);
    float posx = luaL_checknumber(L, 3);
    float posy = luaL_checknumber(L, 4);

    Sketch::instance().text(str, size, posx, posy);
    return 0;
}

int lunaL::rect(lua_State *L) {
    float x1 = luaL_checknumber(L, 1);
    float y1 = luaL_checknumber(L, 2);
    float x2 = luaL_checknumber(L, 3);
    float y2 = luaL_checknumber(L, 4);

    sf::Vector2f p1(x1, y1);
    sf::Vector2f p2(x2, y2);

    Sketch::instance().rect(p1, p2);
    return 0;
}

int lunaL::line(lua_State *L) {
    float x1 = luaL_checknumber(L, 1);
    float y1 = luaL_checknumber(L, 2);
    float x2 = luaL_checknumber(L, 3);
    float y2 = luaL_checknumber(L, 4);

    sf::Vector2f p1(x1, y1);
    sf::Vector2f p2(x2, y2);

    Sketch::instance().line(p1, p2);
    return 0;  
}

int lunaL::circ(lua_State *L) {
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float r = luaL_checknumber(L, 3);

    sf::Vector2f pos(x, y);

    Sketch::instance().circ(pos, r);
    return 0;
}

int lunaL::addShape(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);
    std::string shapeType = luaL_checkstring(L, 2);
    float x = luaL_checknumber(L, 3);
    float y = luaL_checknumber(L, 4);

    std::unique_ptr<sf::Shape> shape;

    if (shapeType == "rectangle") {
        float sizex = luaL_checknumber(L, 5);
        float sizey = luaL_checknumber(L, 6);

        shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(sizex, sizey));
    } else if (shapeType == "circle") {
        float radius = luaL_checknumber(L, 5);

        shape = std::make_unique<sf::CircleShape>(radius);
    } else {
        Logger::instance().logError("Shape type error");
    }

    if (shape) {
        shape->setPosition(x, y);
        Sketch::instance().getShapeMap()[key] = std::move(shape);
    } else {
        Logger::instance().logWarning("Shape not created");
    }

    return 0;
}

int lunaL::editShape(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);
    std::string property = luaL_checkstring(L, 2);

    if (property == "position") {
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);

        Sketch::instance().getShapeMap()[key]->setPosition(x, y);
    } else if (property == "size") {
        float width = luaL_checknumber(L, 3);
        float height = luaL_checknumber(L, 4);

        // TODO: Fix raw pointer workaround
        sf::RectangleShape *s = dynamic_cast<sf::RectangleShape*>(&*Sketch::instance().getShapeMap()[key]);
        if (s)
            s->setSize(sf::Vector2f(width, height));
        else
            Logger::instance().logWarning("Tried to edit radius of a non-rectangular shape");

    } else if (property == "radius") {
        float radius = luaL_checknumber(L, 3);

        // TODO: Fix raw pointer workaround
        sf::CircleShape *s = dynamic_cast<sf::CircleShape*>(&*Sketch::instance().getShapeMap()[key]);
        if (s)
            s->setRadius(radius);
        else
            Logger::instance().logWarning("Tried to edit radius of a non-circular shape");

    } else if (property == "color") {
        int color = luaL_checkinteger(L, 3);

        Sketch::instance().getShapeMap()[key]->setFillColor(sf::Color(color));

    } else if (property == "texture") {
        std::string filePath = luaL_checkstring(L, 3);

        std::map<std::string, sf::Texture*>& tc = Sketch::instance().getTextureCache();
        if (!tc[filePath]) {
            sf::Texture *tex = new sf::Texture;
            tex->loadFromFile(filePath);
            tc[filePath] = tex;
            Logger::instance().logDebug("Loading new texture");
        }
        Sketch::instance().getShapeMap()[key]->setTexture(tc[filePath]);

    } else {
        Logger::instance().logError("Property not found");
    }

    return 0;
}

int lunaL::renderShape(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);

    if (Sketch::instance().getShapeMap()[key])
        Sketch::instance().getWindow().draw( *Sketch::instance().getShapeMap()[key] );

    return 0;
}

int lunaL::removeShape(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);

    if (Sketch::instance().getShapeMap()[key])
        Sketch::instance().getShapeMap().erase(key);

    return 0;
}

int lunaL::addSound(lua_State *L) {
    std::string soundID = luaL_checkstring(L, 1);
    std::string soundPath = luaL_checkstring(L, 2);

    if (!Sketch::instance().getSoundCache()[soundID]) {
        sf::SoundBuffer *bf = new sf::SoundBuffer;
        if (!bf->loadFromFile(soundPath)) {
            Logger::instance().logError("Couldn't load sound");
            return 0;
        }

        std::unique_ptr<sf::Sound> s = std::make_unique<sf::Sound>(*bf);
        Sketch::instance().getSoundCache()[soundID] = std::move(s);
        Logger::instance().logDebug("Loading new sound");
    } else {
        Logger::instance().logError("A sound with the same id is already registered");
    }

    return 0;
}

int lunaL::playSound(lua_State *L) {
    std::string soundID = luaL_checkstring(L, 1);

    if (Sketch::instance().getSoundCache()[soundID]) {
        Sketch::instance().getSoundCache()[soundID]->play();
    } else {
        Logger::instance().logError("Sound not found");
    }

    return 0;
}

int lunaL::pauseSound(lua_State *L) {
    std::string soundID = luaL_checkstring(L, 1);

    if (Sketch::instance().getSoundCache()[soundID]) {
        Sketch::instance().getSoundCache()[soundID]->pause();
    } else {
        Logger::instance().logError("Sound not found");
    }

    return 0;
}

int lunaL::stopSound(lua_State *L) {
    std::string soundID = luaL_checkstring(L, 1);

    if (Sketch::instance().getSoundCache()[soundID]) {
        Sketch::instance().getSoundCache()[soundID]->stop();
    } else {
        Logger::instance().logError("Sound not found");
    }

    return 0;
}