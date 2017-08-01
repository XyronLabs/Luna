local bricks = {}
local ball
local player
local frames = 0

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
	player = { x = width / 2 - 100, sizex = 200 }
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

	if ball.y + ball.radius * 2 > height - 30 then
		if ball.x + ball.radius >= player.x and ball.x + ball.radius <= player.x + player.sizex then
			ball.diry = -1
		end
	end


	clear()

	color(bit32.lshift( bit32.lrotate(0xff0000, math.floor(math.sin(frames) * 0xff0000)), 4) + 0xff)
	for k, v in pairs(bricks) do
		if ball.y <= v.y + v.sizey and ball.y + ball.radius * 2 >= v.y
			and ball.x <= v.x + v.sizex and ball.x + ball.radius * 2 >= v.x then
			ball.diry = 1
			table.remove(bricks, k)
		end
		rect(v.x, v.y, v.sizex, v.sizey)
	end

	color(0xaaaaaaff)
	circ(ball.x, ball.y, ball.radius)
	rect(player.x, height - 30, player.sizex, 20)
	text("Points: " .. 105 - #bricks, 32, 10, 10)

	frames = frames + 0.000000001
end

function input()
	if keys['Left']  then player.x = player.x - 10 end
	if keys['Right'] then player.x = player.x + 10 end
end
