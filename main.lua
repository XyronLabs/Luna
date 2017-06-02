-- Temporary: require colors table
require 'lua.colors'

--[[ Setup function runs only once at startup ]]--
function setup()
    size(1280, 720, "Luna sketch!")

end

--[[ Render function runs once per frame (ex. 60fps) ]]--
function render()
    color(colors.cyan)
    text("Rendering!", 40)
    
    color(colors.red)
    rect(100, 100, 200, 150)
end