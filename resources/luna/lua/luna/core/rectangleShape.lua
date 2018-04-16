--[[ Rectangle class ]]--
rectangleShape = {}
local rectangleShape_mt = { __index = rectangleShape }

rectangleShape.idCounter = 0

--[[ Constructor ]]--
function rectangleShape:new(dat)
    local obj = {}
    obj.id = 'rectangle_' .. rectangleShape.idCounter
    rectangleShape.idCounter = rectangleShape.idCounter + 1
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.x = obj.x or 0
    obj.y = obj.y or 0
    obj.width = obj.width or 0
    obj.height = obj.height or 0
    obj.color = obj.color or colors.white

    setmetatable(obj, rectangleShape_mt)
    registerObject(obj.id, 'rectangle', obj.x, obj.y, obj.width, obj.height)
    editObject(obj.id, 'color', obj.color)
    if obj.texture then editObject(obj.id, 'texture', obj.texture) end
    if obj.outline_color then editObject(obj.id, 'outline_color', obj.outline_color) end
    if obj.outline_thickness then editObject(obj.id, 'outline_thickness', obj.outline_thickness) end
    return obj
end

--[[ Render ]]--
function rectangleShape:render()
    renderObject(self.id)
end

--[[ Setters ]]--
function rectangleShape:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    editObject(self.id, 'position', self.x, self.y)
    return self
end

function rectangleShape:setOrigin(x, y)
    editObject(self.id, 'origin', x, y)
    return self
end

function rectangleShape:setRotation(angle)
    editObject(self.id, 'rotation', angle)
    return self
end

function rectangleShape:setSize(width, height)
    self.width = width or self.width
    self.height = height or self.height
    editObject(self.id, 'size', self.width, self.height)
    return self
end

function rectangleShape:setColor(color)
    self.color = color or self.color
    editObject(self.id, 'color', self.color)
    return self
end

function rectangleShape:setTexture(texturePath)
    self.texture = texturePath
    editObject(self.id, 'texture', texturePath)
    return self
end

function rectangleShape:collide(other)
    return self.x < other.x + other.width and
            self.x + self.width > other.x and
            self.y < other.y + other.height and
            self.y + self.height > other.y
end

function rectangleShape:setOutlineColor(color)
    self.outline_color = color
    editObject(self.id, 'outline_color', color)
    return self
end

function rectangleShape:setOutlineThickness(thickness)
    self.outline_thickness = thickness
    editObject(self.id, 'outline_thickness', thickness)
    return self
end