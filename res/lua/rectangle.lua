--[[ Rectangle class ]]--
rectangle = {}
local rectangle_mt = { __index = rectangle }

--[[ Constructor ]]--
function rectangle:new(dat)
    local obj = {}
    
    obj.x = dat.x or 0
    obj.y = dat.y or 0
    obj.width = dat.width or 0
    obj.height = dat.height or 0
    obj.color = dat.color or colors.white

    setmetatable(obj, rectangle_mt)
    return obj
end

--[[ Render ]]--
function rectangle:render()
    color(self.color)
    rect(self.x, self.y, self.width, self.height)
end

--[[ Setters ]]--
function rectangle:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    return self
end

function rectangle:setSize(width, height)
    self.width = width or self.width
    self.height = height or self.height
    return self
end

function rectangle:setColor(color)
    self.color = color
    return self
end