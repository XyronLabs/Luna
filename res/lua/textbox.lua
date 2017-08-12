--[[ textbox class ]]--
textbox = {}
local textbox_mt = { __index = textbox }

--[[ Constructor ]]--
function textbox:new(dat)
    local obj = {}
    
    obj.x = dat.x or 0
    obj.y = dat.y or 0
    obj.text = dat.text or ""
    obj.size = dat.size or 12
    obj.color = dat.color or colors.white

    setmetatable(obj, textbox_mt)
    registerObject(obj.id, 'text', obj.text, obj.size)
    editObject(obj.id, 'color', obj.color)
    return obj
end

--[[ Render ]]--
function textbox:render()
    -- text(self.text, self.size, self.x, self.y, self.color)
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
    editObject(obj.id, 'text', obj.text)
    return self
end

function textbox:setSize(size)
    self.size = size
    editObject(obj.id, 'textSize', obj.size)
    return self
end