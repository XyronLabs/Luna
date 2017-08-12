--[[ textbox class ]]--
textbox = {}
local textbox_mt = { __index = textbox }

--[[ Constructor ]]--
function textbox:new(dat)
    local obj = {}
    
    obj.x = dat.x or 0
    obj.y = dat.y or 0
    obj.txt = dat.txt or ""
    obj.size = dat.size or 12
    obj.color = dat.color or colors.red

    setmetatable(obj, textbox_mt)
    return obj
end

--[[ Render ]]--
function textbox:render()
    text(self.txt, self.size, self.x, self.y, self.color)
end

--[[ Setters ]]--
function textbox:setPos(x, y)
    self.x = x or self.x
    self.y = y or self.y
    return self
end

function textbox:setText(txt)
    self.txt = txt or self.txt
    return self
end

function textbox:setSize(size)
    self.size = size
    return self
end