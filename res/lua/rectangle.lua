--[[ Rectangle class ]]--
rectangle = {}
local rectangle_mt = { __index = rectangle }

--[[ Constructor ]]--
function rectangle:new(dat)
    local obj = {}
    obj.id = 'rectangle_' .. math.random()
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.x = obj.x or 0
    obj.y = obj.y or 0
    obj.width = obj.width or 0
    obj.height = obj.height or 0
    obj.color = obj.color or colors.white

    setmetatable(obj, rectangle_mt)
    registerObject(obj.id, 'rectangle', obj.x, obj.y, obj.width, obj.height)
    editObject(obj.id, 'color', obj.color)
    if obj.texture then editObject(obj.id, 'texture', obj.texture) end
    return obj
end

--[[ Render ]]--
function rectangle:render()
    renderObject(self.id)
end

--[[ Setters ]]--
function rectangle:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    editObject(self.id, 'position', self.x, self.y)
    return self
end

function rectangle:setSize(width, height)
    self.width = width or self.width
    self.height = height or self.height
    editObject(self.id, 'size', self.width, self.height)
    return self
end

function rectangle:setColor(color)
    self.color = color or self.color
    editObject(self.id, 'color', self.color)
    return self
end

function rectangle:setTexture(texturePath)
    editObject(self.id, 'texture', texturePath)
    return self
end

function rectangle:collide(other)
    return self.x < other.x + other.width and
            self.x + self.width > other.x and
            self.y < other.y + other.height and
            self.y + self.height > other.y
end