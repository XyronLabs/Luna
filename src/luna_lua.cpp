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

    sf::Text t;
    t.setString(str);
    t.setFont(Sketch::instance().getDefaultFont());
    t.setCharacterSize(size);
    t.setPosition(posx, posy);
    t.setFillColor(Sketch::instance().getCurrentColor());

    Sketch::instance().getWindow().draw(t);
    return 0;
}

int lunaL::rect(lua_State *L) {
    float x1 = luaL_checknumber(L, 1);
    float y1 = luaL_checknumber(L, 2);
    float x2 = luaL_checknumber(L, 3);
    float y2 = luaL_checknumber(L, 4);

    sf::RectangleShape box(sf::Vector2f(x2, y2));
    box.setPosition(x1, y1);
    box.setFillColor(Sketch::instance().getCurrentColor());

    Sketch::instance().getWindow().draw(box);
    return 0;
}

int lunaL::line(lua_State *L) {
    float x1 = luaL_checknumber(L, 1);
    float y1 = luaL_checknumber(L, 2);
    float x2 = luaL_checknumber(L, 3);
    float y2 = luaL_checknumber(L, 4);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1), Sketch::instance().getCurrentColor()),
        sf::Vertex(sf::Vector2f(x2, y2), Sketch::instance().getCurrentColor())
    };

    Sketch::instance().getWindow().draw(line, 2, sf::Lines);
    return 0;  
}

/*
    Draw a circle with center at point 'pos'
    and the size 'rx' and 'ry', called from
    ellipse(x,y,rx,ry) Lua function
*/
int lunaL::ellipse(lua_State *L) {
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float rx = luaL_checknumber(L, 3);
    float ry = luaL_checknumber(L, 4);

    sf::CircleShape ellipse(1.f);
    ellipse.setPosition(x, y);
    ellipse.setFillColor(Sketch::instance().getCurrentColor());
    ellipse.setScale(rx, ry);

    Sketch::instance().getWindow().draw(ellipse);
    return 0;
}

int lunaL::registerObject(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);
    std::string objectType = luaL_checkstring(L, 2);
    

    if (objectType == "rectangle") {
        std::unique_ptr<sf::Shape> shape;
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);
        float sizex = luaL_checknumber(L, 5);
        float sizey = luaL_checknumber(L, 6);

        shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(sizex, sizey));
        shape->setPosition(x, y);
        Sketch::instance().getShapeCache()[key] = std::move(shape);

    } else if (objectType == "ellipse") {
        std::unique_ptr<sf::Shape> shape;
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);
        float rx = luaL_checknumber(L, 5);
        float ry = luaL_checknumber(L, 6);

        shape = std::make_unique<sf::CircleShape>(1.f);
        shape->setPosition(x, y);
        shape->scale(rx, ry);
        Sketch::instance().getShapeCache()[key] = std::move(shape);

    } else if (objectType == "text") {
        std::unique_ptr<sf::Text> textBox;
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);
        std::string text = luaL_checkstring(L, 5);
        unsigned int textSize = luaL_checkinteger(L, 6);

        textBox = std::make_unique<sf::Text>(text, Sketch::instance().getDefaultFont(), textSize);
        textBox->setPosition(x, y);
        Sketch::instance().getTextCache()[key] = std::move(textBox);

    } else if (objectType == "sound") {
        std::string soundPath = luaL_checkstring(L, 3);
    
        if (!Sketch::instance().getSoundCache()[key]) {
            sf::SoundBuffer *bf = new sf::SoundBuffer;
            if (!bf->loadFromFile(soundPath)) {
                Logger::instance().log(Logger::Level::ERROR, {"Couldn't load sound"});
                return 0;
            }
    
            std::unique_ptr<sf::Sound> s = std::make_unique<sf::Sound>(*bf);
            Sketch::instance().getSoundCache()[key] = std::move(s);
            Logger::instance().log(Logger::Level::DEBUG, {"Loading new sound"});
        } else {
            Logger::instance().log(Logger::Level::ERROR, {"A sound with the same id is already registered"});
        }

    } else {
        Logger::instance().log(Logger::Level::ERROR, {"Object type error: id=", key, " type=", objectType});
    }

    return 0;
}

int lunaL::editObject(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);
    std::string property = luaL_checkstring(L, 2);

    if (property == "position") {
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);

        if (Sketch::instance().getShapeCache()[key])
            Sketch::instance().getShapeCache()[key]->setPosition(x, y);
        else if (Sketch::instance().getTextCache()[key])
            Sketch::instance().getTextCache()[key]->setPosition(x, y);

    } else if (property == "size") {
        float width = luaL_checknumber(L, 3);
        float height = luaL_checknumber(L, 4);

        // TODO: Fix raw pointer workaround
        sf::RectangleShape *s = dynamic_cast<sf::RectangleShape*>(&*Sketch::instance().getShapeCache()[key]);
        if (s)
            s->setSize(sf::Vector2f(width, height));
        else
            Logger::instance().log(Logger::Level::WARNING, {"Tried to edit radius of a non-rectangular shape"});

    } else if (property == "radius") {
        float xradius = luaL_checknumber(L, 3);
        float yradius = luaL_checknumber(L, 4);

        // TODO: Fix raw pointer workaround
        sf::CircleShape *s = dynamic_cast<sf::CircleShape*>(&*Sketch::instance().getShapeCache()[key]);
        if (s)
            s->setScale(xradius, yradius);
        else
            Logger::instance().log(Logger::Level::WARNING, {"Tried to edit radius of a non-circular shape"});

    } else if (property == "color") {
        int color = luaL_checkinteger(L, 3);

        if (Sketch::instance().getShapeCache()[key])
            Sketch::instance().getShapeCache()[key]->setFillColor(sf::Color(color));
        else if (Sketch::instance().getTextCache()[key])
            Sketch::instance().getTextCache()[key]->setFillColor(sf::Color(color));

    } else if (property == "texture") {
        std::string filePath = luaL_checkstring(L, 3);

        std::map<std::string, sf::Texture*>& tc = Sketch::instance().getTextureCache();
        if (!tc[filePath]) {
            sf::Texture *tex = new sf::Texture;
            tex->loadFromFile(filePath);
            tc[filePath] = tex;
            Logger::instance().log(Logger::Level::DEBUG, {"Loading new texture"});
        }
        Sketch::instance().getShapeCache()[key]->setTexture(tc[filePath]);

    } else if (property == "text") {
        std::string text = luaL_checkstring(L, 3);

        Sketch::instance().getTextCache()[key]->setString(text);

    } else if (property == "textSize") {
        unsigned int textSize = luaL_checkinteger(L, 3);
        
        Sketch::instance().getTextCache()[key]->setCharacterSize(textSize);

    } else if (property == "play") {
        
        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->play();
        } else {
            Logger::instance().log(Logger::Level::ERROR, {"Sound not found"});
        }

    } else if (property == "pause") {
        std::string soundID = luaL_checkstring(L, 3);
        
        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->pause();
        } else {
            Logger::instance().log(Logger::Level::ERROR, {"Sound not found"});
        }

    } else if (property == "stop") {
        std::string soundID = luaL_checkstring(L, 3);
        
        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->stop();
        } else {
            Logger::instance().log(Logger::Level::ERROR, {"Sound not found"});
        }

    } else {
        Logger::instance().log(Logger::Level::ERROR, {"Property not found"});
    }

    return 0;
}

int lunaL::renderObject(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);

    if (Sketch::instance().getShapeCache()[key])
        Sketch::instance().getWindow().draw( *Sketch::instance().getShapeCache()[key] );
    else if (Sketch::instance().getTextCache()[key])
        Sketch::instance().getWindow().draw( *Sketch::instance().getTextCache()[key] );

    return 0;
}

int lunaL::removeObject(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);

    if (Sketch::instance().getShapeCache()[key])
        Sketch::instance().getShapeCache().erase(key);
    if (Sketch::instance().getTextCache()[key])
        Sketch::instance().getTextCache().erase(key);
    if (Sketch::instance().getSoundCache()[key])
        Sketch::instance().getSoundCache().erase(key);

    return 0;
}

int lunaL::log(lua_State *L) {
    int level = luaL_checkinteger(L, 1);
    std::string message = luaL_checkstring(L, 2);

    Logger::instance().log(static_cast<Logger::Level>(level), {message});

    return 0;
}

int lunaL::frameRate(lua_State *L) {
    int fps = luaL_checkinteger(L, 1);

    Sketch::instance().getWindow().setFramerateLimit(fps);

    return 0;
}

int lunaL::exit(lua_State *L) {
    Sketch::instance().getWindow().close();

    return 0;
}