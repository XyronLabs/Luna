-- Temporary: require colors table
require 'lua.colors'
local x, y = 0, 0

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
end