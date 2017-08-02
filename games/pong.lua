local player1, player2
local ball

function setup()
    size(800, 600, "Pong!")

    player1 = rectangle:new{ x = 20, y = height / 2, width = 20, height = 100, points = 0 }
    player2 = rectangle:new{ x = width - 40, y = height / 2, width = 20, height = 100, points = 0 }

    ball = circle:new{ x = width / 2, y = height / 2, dirx = 1, diry = 1, radius = 20, speed = 5 }
end

function render()
    clear()
    text(player1.points .. " : " .. player2.points, 50, width / 2 - 50, 10)

    -- Check collisions
    if ball.x + ball.radius * 2  >= width then
        ball.x = width / 2
        ball.y = height / 2
        player1.points = player1.points + 1
    end
    if ball.x <= 0 then
        ball.x = width / 2
        ball.y = height / 2
        player2.points = player2.points + 1
    end
    if ball.y + ball.radius * 2 >= height or ball.y <= 0 then
        ball.diry = ball.diry * -1
    end
    if ball.x + ball.radius >= player2.x and ball.y + ball.radius*2 >= player2.y and ball.y <= player2.y+100 then
        ball.dirx = ball.dirx * -1
    end
    if ball.x + ball.radius <= player1.x+20 and ball.y + ball.radius*2 >= player1.y and ball.y <= player1.y+100 then
        ball.dirx = ball.dirx * -1
    end

    -- Update position
    ball:setPos(ball.x + ball.dirx * ball.speed, ball.y + ball.diry * ball.speed)

    color(colors.white)
    player1:render()
    player2:render()

    ball:render()
end

function input()
    if keys['Q'] then
        player1:setPos(nil, player1.y - 5)
    elseif keys['A'] then
        player1:setPos(nil, player1.y + 5)
    end

    if keys['P'] then
        player2:setPos(nil, player2.y - 5)
    elseif keys['L'] then
        player2:setPos(nil, player2.y + 5)
    end
end