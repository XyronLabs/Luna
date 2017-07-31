--[[ Circle class ]]--
circle = {}
local circle_mt = { __index = circle }

--[[ Constructor ]]--
function circle:new(dat)
    local obj = {}
    
    obj.x = dat.x or 0
    obj.y = dat.y or 0
    obj.radius = dat.radius or 0
    obj.color = dat.color or colors.white

    setmetatable(obj, circle_mt)
    return obj
end

--[[ Render ]]--
function circle:render()
    color(self.color)
    circ(self.x, self.y, self.radius)
end

--[[ Setters ]]--
function circle:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    return self
end

function circle:setRadius(radius)
    self.radius = radius or self.radius
    return self
end

function circle:setColor(color)
    self.color = color
    return self
end