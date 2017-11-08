require 'math.vector'

particle = {}

function particle:new(dat)
    local obj = dat or {}

    obj.pos = obj.pos or vector:new(0, 0)
    obj.vel = obj.vel or vector:new(0, 0)
    obj.acc = obj.acc or vector:new(0, 0)

    obj.renderer = obj.renderer or ellipseShape:new{ x = obj.pos.x, y = obj.pos.y, xradius = 5, yradius = 5, color = colors.white }

    setmetatable(obj, { __index = particle })
    return obj
end

function particle:update()
    self.vel:add(self.acc)
    self.pos:add(self.vel)
    self.acc:mul(0)

    self.renderer:setPos(self.pos.x, self.pos.y)
end

function particle:render()
    self.renderer:render()
end

function particle:applyForce(force)
    self.acc:add(force)
end