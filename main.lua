-- Temporary: require colors table
require 'lua.colors'
require 'lua.rectangle'

local x, y = 0, 0

local rect1 = rectangle:new{ x=20, y=80, width=100, height=100, color=colors.green }

--[[ Setup function runs only once at startup ]]--
function setup()
    size(1280, 720, "Luna sketch!")
end

--[[ Render function runs once per frame (ex. 60fps) ]]--
function render()
    color(colors.cyan)
    text("Rendering!", 40)
    
    color(colors.red)
    rect(100 + x, 100 + y, 200, 150)
    x = x + 1
    y = y + 1

    color(colors.white)
    rect1:render()
end