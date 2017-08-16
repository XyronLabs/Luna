--[[ Ellipse class ]]--
ellipseShape = {}
local ellipseShape_mt = { __index = ellipseShape }

--[[ Constructor ]]--
function ellipseShape:new(dat)
    local obj = {}
    obj.id = 'ellipseShape_' .. math.random()
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.x = obj.x or 0
    obj.y = obj.y or 0
    obj.xradius = obj.xradius or obj.radius or 0
    obj.yradius = obj.yradius or obj.radius or 0
    obj.color = obj.color or colors.white


    setmetatable(obj, ellipseShape_mt)
    registerObject(obj.id, 'ellipse', obj.x, obj.y, obj.xradius, obj.yradius)
    editObject(obj.id, 'color', obj.color)
    if obj.texture then editShape(obj.id, 'texture', obj.texture) end
    return obj
end

--[[ Render ]]--
function ellipseShape:render()
    renderObject(self.id)
end

--[[ Setters ]]--
function ellipseShape:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    editObject(self.id, 'position', self.x, self.y)
    return self
end

function ellipseShape:setRadius(xradius, yradius)
    self.xradius = xradius or self.xradius
    self.yradius = yradius or xradius or self.yradius
    editObject(self.id, 'radius', self.xradius, self.yradius)
    return self
end

function ellipseShape:setColor(color)
    self.color = color or self.color
    editObject(self.id, 'color', self.color)
    return self
end

function ellipseShape:setTexture(texturePath)
    editObject(self.id, 'texture', texturePath)
    return self
end

function ellipseShape:dist(other)
    return math.sqrt( (other.x - self.x) * (other.x - self.x) + (other.y - self.y) * (other.y - self.y) )
end

function ellipseShape:collide(other)
    return self:dist(other) < self.radius + other.radius
end