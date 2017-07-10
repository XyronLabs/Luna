local player = {
    name = "Alex",
    x = 1,
    y = 1,
    dirx = 1,
    diry = 1,
    speed = 2,
    rad = 20
}

function setup()
    size(1280, 720, "Test Game!")
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
    text("Player: " .. player.name, 32)
    color(colors.yellow)
    circ(player.x, player.y, player.rad)
end

function input()
    if keys[key] == 'Up'    then player.diry = -1 end
    if keys[key] == 'Down'  then player.diry =  1 end
    if keys[key] == 'Left'  then player.dirx = -1 end
    if keys[key] == 'Right' then player.dirx =  1 end
    
    if keys[key] == 'Period' then player.speed = player.speed + 0.1 end
    if keys[key] == 'Comma' then player.speed = player.speed - 0.1 end
end