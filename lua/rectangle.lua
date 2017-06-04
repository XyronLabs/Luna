rectangle = {}
local rectangle_mt = {
    __index = rectangle
}

function rectangle:new(dat)
    local obj = self or {}
    
    obj.x = dat.x or 0
    obj.y = dat.y or 0
    obj.width = dat.width or 0
    obj.height = dat.height or 0
    obj.color = dat.color or colors.white

    setmetatable(self, rectangle_mt)
    return obj
end

function rectangle:render()
    color(self.color)
    rect(self.x, self.y, self.width, self.height)
end