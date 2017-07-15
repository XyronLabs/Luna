local bricks = {}
local ball
local player

function newBrick(x, y)
	return { x = x, y = y, sizex = 40, sizey = 20 }
end

function setup()
	size(800, 600, "Luna Breakout")

	for i = 1, 15 do
		for j = 1, 7 do
			table.insert(bricks, newBrick(i*50, j*30))
		end
	end

	ball = { x = width / 2, y = height - 50, dirx = 1, diry = -1, speed = 5, radius = 20 }
	player = { x = width / 2 - 50, sizex = 100 }
end

function render()

	if ball.x + ball.radius * 2  >= width or ball.x <= 0 then
		ball.dirx = ball.dirx * -1
	end
    
	if ball.y <= 0 then
		ball.diry = ball.diry * -1
	end

    if ball.y + ball.radius * 2 >= height then
        ball.x = width / 2
        ball.y = height - 50
        ball.diry = -1
    end

	ball.x = ball.x + ball.dirx * ball.speed
	ball.y = ball.y + ball.diry * ball.speed

	if ball.x + ball.radius * 2  <= player.x+player.sizex and ball.x >= player.x
	and ball.y+ball.sizey >= height - 30 then
		ball.diry = ball.diry * -1
	end


	clear()

	for k, v in pairs(bricks) do
        if ball.x + ball.radius <= v.x+v.sizex and ball.x + ball.radius >= v.x
		and (ball.y == v.y+v.sizey or ball.y+ball.radius*2 == v.y) then
			ball.diry = ball.diry * -1
			table.remove(bricks, k)
		end
		rect(v.x, v.y, v.sizex, v.sizey)
	end

	circ(ball.x, ball.y, ball.radius)
	rect(player.x, height - 30, player.sizex, 20)
end

function input()
	if keys['Left']  then player.x = player.x - 5 end
	if keys['Right'] then player.x = player.x + 5 end
end
