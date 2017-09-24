--[[ CustomShape class ]]--
customShape = {}
local customShape_mt = { __index = customShape }

--[[ Constructor ]]--
function customShape:new(dat)
    local obj = {}
    obj.id = 'customShape_' .. math.random()
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.points = obj.points or {}
    obj.color = obj.color or colors.white

    setmetatable(obj, customShape_mt)
    registerObject(obj.id, 'custom', #obj.points)
    for i = 1, #obj.points do
        editObject(obj.id, 'vertex', i - 1, obj.points[i][1], obj.points[i][2])
    end
    editObject(obj.id, 'color', obj.color)
    if obj.texture then editShape(obj.id, 'texture', obj.texture) end
    return obj
end

--[[ Render ]]--
function customShape:render()
    renderObject(self.id)
end

--[[ Setters ]]--
function customShape:setOrigin(x, y)
    editObject(self.id, 'origin', x, y)
    return self
end

function customShape:setRotation(angle)
    editObject(self.id, 'rotation', angle)
    return self
end

function customShape:setColor(color)
    self.color = color or self.color
    editObject(self.id, 'color', self.color)
    return self
end

function customShape:setTexture(texturePath)
    editObject(self.id, 'texture', texturePath)
    return self
end

function customShape:setOutlineColor(color)
    editObject(self.id, 'outline_color', color)
    return self
end

function customShape:setOutlineThickness(thickness)
    editObject(self.id, 'outline_thickness', thickness)
    return self
end