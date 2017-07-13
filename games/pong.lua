local player1, player2
local ball

function setup()
    size(800, 600, "Pong!")

    player1 = { x = 20, y = height / 2, points = 0 }
    player2 = { x = width - 40, y = height / 2, points = 0 }

    ball = { x = width / 2, y = height / 2, dirx = 1, diry = 1, radius = 20, speed = 5 }
end

function render()
    clear()
    text("\t\t\t\t\t\t\t" .. player1.points .. " : " .. player2.points, 50)

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
    ball.x = ball.x + ball.dirx * ball.speed
    ball.y = ball.y + ball.diry * ball.speed

    color(colors.white)
    rect(player1.x, player1.y, 20, 100)
    rect(player2.x, player2.y, 20, 100)

    circ(ball.x, ball.y, ball.radius)
end

function input()
    if keys[key] == 'Q' then
        player1.y = player1.y - 5
    elseif keys[key] == 'A' then
        player1.y = player1.y + 5
    end

    if keys[key] == 'P' then
        player2.y = player2.y - 5
    elseif keys[key] == 'L' then
        player2.y = player2.y + 5
    end
end