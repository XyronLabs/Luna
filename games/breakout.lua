local bricks = {}
local ball
local player
local frames = 0

local popSound

function newBrick(x, y)
	return rectangle:new{ x = x, y = y, width = 40, height = 20, texture = "test/textures/brick.png" }
end

function setup()
	size(800, 600, "Luna Breakout")

	for i = 1, 15 do
		for j = 1, 7 do
			table.insert(bricks, newBrick(i*50, j*30))
		end
	end

	ball = circle:new{ x = width / 2, y = height - 50, dirx = 1, diry = -1, speed = 5, radius = 20, color = colors.cyan }
	player = rectangle:new{ x = width / 2 - 100, y = height - 30, width = 200, height = 20, texture = "test/textures/player.png" }

	popSound = sound:new{ path = "test/pop.wav" }
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

	ball:setPos(ball.x + ball.dirx * ball.speed, ball.y + ball.diry * ball.speed)

	if ball.y + ball.radius * 2 > player.y and ball.y < player.y + player.height then
		if ball.x + ball.radius >= player.x and ball.x + ball.radius <= player.x + player.width then
			ball.diry = -1
			popSound:play()
		end
	end


	clear()

	
	for k, v in pairs(bricks) do
		v:setColor(hsva(frames % 1, 1, 1, 1))
		if ball.y <= v.y + v.height and ball.y + ball.radius * 2 >= v.y
			and ball.x <= v.x + v.width and ball.x + ball.radius * 2 >= v.x then
			ball.diry = 1
			table.remove(bricks, k)
			--removeShape(v.id) -- remove shape from shapeMap
		end
		v:render()
	end

	color(0xaaaaaaff)
	ball:render()
	player:render()
	text("Points: " .. 105 - #bricks, 32, 10, 10, colors.white)

	frames = frames + 0.001
	
end

function input()
	if keys['Left']  then player:setPos(player.x - 10) end
	if keys['Right'] then player:setPos(player.x + 10) end
	
	if mousekeys['Left'] then player:setPos(mouseX - player.width / 2, mouseY - player.height / 2) end
end
