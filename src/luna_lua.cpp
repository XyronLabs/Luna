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
    float sizex = luaL_checknumber(L, 5);
    float sizey = luaL_checknumber(L, 6);

    std::unique_ptr<sf::Shape> shape;

    if (shapeType == "rectangle") {
        shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(sizex, sizey));
    } else if (shapeType == "circle") {
        shape = std::make_unique<sf::CircleShape>(sizex);
    } else {
        Logger::instance().logError("Shape type error");
    }

    if (shape) {
        shape->setPosition(x, y);
        Sketch::instance().getShapeMap()[key] = std::move(shape);
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
        (dynamic_cast<sf::RectangleShape*>(&*Sketch::instance().getShapeMap()[key]))->setSize(sf::Vector2f(width, height));
    } else if (property == "radius") {
        float radius = luaL_checknumber(L, 3);

        // TODO: Fix raw pointer workaround
        (dynamic_cast<sf::CircleShape*>(&*Sketch::instance().getShapeMap()[key]))->setRadius(radius);
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