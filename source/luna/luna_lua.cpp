#include "luna/luna_lua.hpp"
#include "luna/Logger.hpp"
#include "luna/LunaConf.hpp"

/***************************** Common functions ******************************/

int lunaL::size(lua_State *L) {
    int w = luaL_checkinteger(L, 1);
    int h = luaL_checkinteger(L, 2);
    const char* t = luaL_checkstring(L, 3);

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

int lunaL::log(lua_State *L) {
    int level = luaL_checkinteger(L, 1);
    std::string message = luaL_checkstring(L, 2);

    Logger::instance().log(static_cast<Logger::Level>(level), { message });
    return 0;
}

int lunaL::setLogLevel(lua_State *L) {
    int level = luaL_checkinteger(L, 1);

    Logger::instance().setLevel(static_cast<Logger::Level>(level));
    return 0;
}

int lunaL::framerate(lua_State *L) {
    int fps = luaL_checkinteger(L, 1);

    Sketch::instance().getWindow().setFramerateLimit(fps);
    return 0;
}

int lunaL::exit(lua_State *L) {
    Sketch::instance().getWindow().close();
    return 0;
}

int lunaL::icon(lua_State *L) {
    std::string iconPath = luaL_checkstring(L, 1);

    sf::Image icon;
    icon.loadFromFile(iconPath);
    Sketch::instance().getWindow().setIcon(256, 256, icon.getPixelsPtr());
    return 0;
}

int lunaL::noLoop(lua_State *L) {
    Sketch::instance().noLoop();
    return 0;
}

int lunaL::setMouseVisible(lua_State *L) {
    if (lua_isboolean(L, 1)) {
        Sketch::instance().getWindow().setMouseCursorVisible(lua_toboolean(L, 1));
    }
    return 0;
}


/***************************** Simple rendering ******************************/

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
    float coords[4];
    for (int i = 0; i < 4; ++i)
        coords[i] = luaL_checknumber(L, i + 1);

    const sf::Color& currColor = Sketch::instance().getCurrentColor();
    sf::VertexArray v(sf::Quads, 4);
    v[0] = sf::Vertex(sf::Vector2f(coords[0]            , coords[1]            ), currColor);
    v[1] = sf::Vertex(sf::Vector2f(coords[0]            , coords[1] + coords[3]), currColor);
    v[2] = sf::Vertex(sf::Vector2f(coords[0] + coords[2], coords[1] + coords[3]), currColor);
    v[3] = sf::Vertex(sf::Vector2f(coords[0] + coords[2], coords[1]            ), currColor);


    Sketch::instance().getWindow().draw(v);
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


/************************* Object oriented rendering *************************/

int lunaL::registerObject(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);
    std::string objectType = luaL_checkstring(L, 2);


    if (objectType == "rectangle") {
        sf::Shape *shape;
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);
        float sizex = luaL_checknumber(L, 5);
        float sizey = luaL_checknumber(L, 6);

        shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
        shape->setPosition(x, y);
        Sketch::instance().getShapeCache()[key] = shape;
        // Sketch::instance().getShapeCache().insert(std::pair<std::string, sf::Shape*>(key, shape));

    } else if (objectType == "ellipse") {
        sf::Shape* shape;
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);
        float rx = luaL_checknumber(L, 5);
        float ry = luaL_checknumber(L, 6);

        shape = new sf::CircleShape(1.f);
        shape->setPosition(x, y);
        shape->scale(rx, ry);
        Sketch::instance().getShapeCache()[key] = shape;

    } else if (objectType == "text") {
        sf::Text* textBox;
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);
        std::string text = luaL_checkstring(L, 5);
        unsigned int textSize = luaL_checkinteger(L, 6);

        textBox = new sf::Text(text, Sketch::instance().getDefaultFont(), textSize);
        textBox->setPosition(x, y);
        Sketch::instance().getTextCache()[key] = textBox;

    } else if (objectType == "sound") {
        std::string soundPath = luaL_checkstring(L, 3);

        if (!Sketch::instance().getSoundCache()[key]) {
            sf::SoundBuffer *bf = new sf::SoundBuffer;
            if (!bf->loadFromFile(soundPath)) {
                Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_sound_cant_load") });
                return 0;
            }

            sf::Sound* s = new sf::Sound(*bf);
            Sketch::instance().getSoundCache()[key] = s;
            Logger::instance().log(Logger::Level::DEBUG, {"Loading new sound"});
        } else {
            Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_sound_already_registered") });
        }

    } else if (objectType == "custom") {
        sf::Shape* shape;
        int points = luaL_checkinteger(L, 3);

        sf::ConvexShape s;
        s.setPointCount(points);
        shape = new sf::ConvexShape(s);

        Sketch::instance().getShapeCache()[key] = shape;

    } else {
        Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_object_type"), key, luna_conf::lang.get("error_object_type_2"), objectType});
    }

    return 0;
}

int lunaL::editObject(lua_State *L) {
    std::string key = luaL_checkstring(L, 1);
    std::string property = luaL_checkstring(L, 2);

/***************************** Common properties ******************************/
    if (property == "position") {
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);

        if (Sketch::instance().getShapeCache()[key])
            Sketch::instance().getShapeCache()[key]->setPosition(x, y);
        else if (Sketch::instance().getTextCache()[key])
            Sketch::instance().getTextCache()[key]->setPosition(x, y);

    } else if (property == "origin") {
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);

        if (Sketch::instance().getShapeCache()[key])
            Sketch::instance().getShapeCache()[key]->setOrigin(x, y);
        else if (Sketch::instance().getTextCache()[key])
            Sketch::instance().getTextCache()[key]->setOrigin(x, y);

    } else if (property == "rotation") {
        float angle = luaL_checknumber(L, 3);

        if (Sketch::instance().getShapeCache()[key])
            Sketch::instance().getShapeCache()[key]->setRotation(angle);
        else if (Sketch::instance().getTextCache()[key])
            Sketch::instance().getTextCache()[key]->setRotation(angle);

    } else if (property == "outline_color") {
        int color = luaL_checkinteger(L, 3);

        if (Sketch::instance().getShapeCache()[key])
            Sketch::instance().getShapeCache()[key]->setOutlineColor(sf::Color(color));
        else if (Sketch::instance().getTextCache()[key])
            Sketch::instance().getTextCache()[key]->setOutlineColor(sf::Color(color));

    } else if (property == "outline_thickness") {
        float thickness = luaL_checknumber(L, 3);

        if (Sketch::instance().getShapeCache()[key])
            Sketch::instance().getShapeCache()[key]->setOutlineThickness(thickness);
        else if (Sketch::instance().getTextCache()[key])
            Sketch::instance().getTextCache()[key]->setOutlineThickness(thickness);

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


/*************************** Rectangle properties *****************************/
    } else if (property == "size") {
        float width = luaL_checknumber(L, 3);
        float height = luaL_checknumber(L, 4);

        sf::RectangleShape *s = static_cast<sf::RectangleShape*>(Sketch::instance().getShapeCache()[key]);
        if (s)
            s->setSize(sf::Vector2f(width, height));
        else
            Logger::instance().log(Logger::Level::WARNING, { luna_conf::lang.get("error_size_non_rectangular") });


/**************************** Circle properties *******************************/
    } else if (property == "radius") {
        float xradius = luaL_checknumber(L, 3);
        float yradius = luaL_checknumber(L, 4);

        sf::CircleShape *s = static_cast<sf::CircleShape*>(Sketch::instance().getShapeCache()[key]);
        if (s)
            s->setScale(xradius, yradius);
        else
            Logger::instance().log(Logger::Level::WARNING, { luna_conf::lang.get("error_radius_non_circular") });


/************************** Custom shape properties ***************************/
} else if (property == "vertex") {
    int index = luaL_checkinteger(L, 3);
    float x = luaL_checknumber(L, 4);
    float y = luaL_checknumber(L, 5);

    sf::ConvexShape *s = static_cast<sf::ConvexShape*>(Sketch::instance().getShapeCache()[key]);

    if (s)
        s->setPoint(index, sf::Vector2f(x, y));
    else
        Logger::instance().log(Logger::Level::WARNING, { luna_conf::lang.get("error_not_custom_shape") });


/****************************** Text properties *******************************/
    } else if (property == "text") {
        std::string text = luaL_checkstring(L, 3);

        Sketch::instance().getTextCache()[key]->setString(text);

    } else if (property == "textSize") {
        unsigned int textSize = luaL_checkinteger(L, 3);

        Sketch::instance().getTextCache()[key]->setCharacterSize(textSize);


/****************************** Sound properties ******************************/
    } else if (property == "play") {

        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->play();
        } else {
            Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_sound_not_found") });
        }

    } else if (property == "pause") {
        std::string soundID = luaL_checkstring(L, 3);

        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->pause();
        } else {
            Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_sound_not_found") });
        }

    } else if (property == "stop") {
        std::string soundID = luaL_checkstring(L, 3);

        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->stop();
        } else {
            Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_sound_not_found") });
        }

    } else if (property == "volume") {
        float volume = luaL_checknumber(L, 3);

        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->setVolume(volume);
        } else {
            Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_sound_not_found") });
        }

    } else if (property == "loop") {
        bool loop = lua_toboolean(L, 3);

        if (Sketch::instance().getSoundCache()[key]) {
            Sketch::instance().getSoundCache()[key]->setLoop(loop);
        } else {
            Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_sound_not_found") });
        }


    } else {
        Logger::instance().log(Logger::Level::ERROR, { luna_conf::lang.get("error_property_not_found") });
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