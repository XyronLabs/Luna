local player = {
    name = "Alex",
    x = 1,
    y = 1,
    dirx = 1,
    diry = 1,
    speed = 2,
    rad = 20
}
local t1
function setup()
    size(1280, 720, "Test Game!")
    t1 = textbox:new{ text = "Lololo", size = 40, x = 500, y = 500}
end

function render()
    clear()
    
    -- Check collisions
    if player.x + player.rad * 2  >= width or player.x <= 0 then
        player.dirx = player.dirx * -1
    end
    if player.y + player.rad * 2 >= height or player.y <= 0 then
        player.diry = player.diry * -1
    end

    -- Update position
    player.x = player.x + player.dirx * player.speed
    player.y = player.y + player.diry * player.speed

    -- Render
    text("Player: " .. player.name, 32, 10, 10, colors.white)
    color(0x2233aaff)
    circ(player.x, player.y, player.rad)
    t1:render()
    t1:setPos(100, 100)
end

function input()
    if keys['Up']    then player.diry = -1 end
    if keys['Down']  then player.diry =  1 end
    if keys['Left']  then player.dirx = -1 end
    if keys['Right'] then player.dirx =  1 end
    
    if keys['Period'] then player.speed = player.speed + 0.1 end
    if keys['Comma']  then player.speed = player.speed - 0.1 end
end