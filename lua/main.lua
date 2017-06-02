
--[[ Setup function runs only once at startup ]]--
function setup()
    size(1280, 720, "Luna sketch!")

end

--[[ Render function runs once per frame (ex. 60fps) ]]--
function render()
    text("Rendering!", 40)
    rect(100, 100, 200, 150)
end