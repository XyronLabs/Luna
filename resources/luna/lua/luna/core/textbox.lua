--[[ textbox class ]]--
textbox = {}
local textbox_mt = { __index = textbox }

textbox.idCounter = 0

--[[ Constructor ]]--
function textbox:new(dat)
    local obj = {}
    obj.id = 'text_' .. textbox.idCounter
    textbox.idCounter = textbox.idCounter + 1
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.x = obj.x or 0
    obj.y = obj.y or 0
    obj.text = obj.text or ""
    obj.size = obj.size or 12
    obj.color = obj.color or colors.white

    setmetatable(obj, textbox_mt)
    registerObject(obj.id, 'text', obj.x, obj.y, obj.text, obj.size)
    editObject(obj.id, 'color', obj.color)
    if obj.outline_color then editObject(obj.id, 'outline_color', obj.outline_color) end
    if obj.outline_thickness then editObject(obj.id, 'outline_thickness', obj.outline_thickness) end
    return obj
end

--[[ Render ]]--
function textbox:render()
    renderObject(self.id)
end

--[[ Setters ]]--
function textbox:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    editObject(self.id, 'position', self.x, self.y)
    return self
end

function textbox:setText(text)
    self.text = text or self.text
    editObject(self.id, 'text', self.text)
    return self
end

function textbox:setSize(size)
    self.size = size
    editObject(self.id, 'textSize', self.size)
    return self
end

function textbox:setColor(color)
    self.color = color or self.color
    editObject(self.id, 'color', self.color)
    return self
end

function textbox:setOutlineColor(color)
    self.outline_color = color
    editObject(self.id, 'outline_color', color)
    return self
end

function textbox:setOutlineThickness(thickness)
    self.outline_thickness = thickness
    editObject(self.id, 'outline_thickness', thickness)
    return self
end