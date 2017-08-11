--[[ Circle class ]]--
circle = {}
local circle_mt = { __index = circle }

--[[ Constructor ]]--
function circle:new(dat)
    local obj = {}
    obj.id = 'circle_' .. math.random()
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.x = obj.x or 0
    obj.y = obj.y or 0
    obj.radius = obj.radius or 0
    obj.color = obj.color or colors.white


    setmetatable(obj, circle_mt)
    addShape(obj.id, 'circle', obj.x, obj.y, obj.radius, 0)
    editShape(obj.id, 'color', obj.color)
    return obj
end

--[[ Render ]]--
function circle:render()
    renderShape(self.id)
end

--[[ Setters ]]--
function circle:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    editShape(self.id, 'position', self.x, self.y)
    return self
end

function circle:setRadius(radius)
    self.radius = radius or self.radius
    editShape(self.id, 'radius', self.radius)
    return self
end

function circle:setColor(color)
    self.color = color or self.color
    editShape(self.id, 'color', self.color)
    return self
end

function circle:setTexture(texturePath)
    editShape(self.id, 'texture', texturePath)
    return self
end

function circle:dist(other)
    return math.sqrt( (other.x - self.x) * (other.x - self.x) + (other.y - self.y) * (other.y - self.y) )
end

function circle:collide(other)
    return self:dist(other) < self.radius + other.radius
end