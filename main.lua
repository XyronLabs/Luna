-- Temporary: require libraries manually
require 'lua.colors'
require 'lua.rectangle'
require 'lua.circle'

local rect1 = rectangle:new{ x=20, y=80, width=100, height=100, color=colors.green }
local rect2 = rectangle:new{}:setPos(400, 400):setSize(10, 10):setColor(colors.blue)

local circle1 = circle:new{ x=500, y=100, radius=25 }

--[[ Setup function runs only once at startup ]]--
function setup()
    size(1280, 720, "Luna sketch!")
end

--[[ Render function runs once per frame (ex. 60fps) ]]--
function render()
    color(colors.cyan)
    text("Rendering!", 40)

    rect1:render()
    rect2:render()

    rect2:setPos(rect2.x+1, rect2.y)

    circle1:render()
end