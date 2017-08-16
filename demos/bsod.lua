local msg = [[
    Your PC ran into a problem and needs to be restarted
    as soon as we're finished stealing your data...
    
    101%
]]

function setup()
    size(1024, 600, "Something went wrong :(")
end

function render()
    clear()

    color(0x0078D7FF)
    rect(0, 0, width, height)

    color(colors.white)
    text(":(", 200, 75, 40)

    text(msg, 32, 100, 350)
end