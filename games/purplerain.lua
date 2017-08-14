local drops = {}

function setup()
    size(1280, 720, "Purple rain demo")

    for i = 1, 1000 do
        table.insert(drops, { x = math.random(0, width), y = math.random(-500, -50), speed = math.random(0, 30) / 30, g = math.random(1, 20) / 20 })
    end
end

function render()
    clear()
    color(colors.white)
    rect(0, 0, width, height)

    color(0x8811BBFF)
    for i = 1, 1000 do
        drops[i].y = drops[i].y + drops[i].speed
        drops[i].speed = drops[i].speed + drops[i].g

        if drops[i].y > height then
            drops[i].y = math.random(-500, -50)
            drops[i].speed = math.random(0, 30) / 30
        end
        
        line(drops[i].x, drops[i].y, drops[i].x, drops[i].y + drops[i].speed)
    end
end