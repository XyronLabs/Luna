local startAngle, nDivAngle = math.pi / 2, 3
local numBranches, maxBranches = 0, 5
local speed = 0.01

function setup()
    size(1024, 1024, "Fractal tree demo")
end

function render()
    clear()
    numBranches = 0
    branch(width / 2, height *5/ 6, -200, startAngle, 0)
end

function branch(x, y, len, angle, n)
    numBranches = numBranches + 1
    local nx, ny = x + len * math.cos(angle), y + len * math.sin(angle)
    line(x, y, nx, ny)
    
    if n < maxBranches then
        branch(nx, ny, len * 0.75, angle + startAngle / nDivAngle, n + 1)
        branch(nx, ny, len * 0.75, angle - startAngle / nDivAngle, n + 1)
    end
end

function input()
    if keys['Z'] then startAngle = startAngle - speed end
    if keys['X'] then startAngle = startAngle + speed end
    
    if keys['A'] then nDivAngle = nDivAngle - speed end
    if keys['S'] then nDivAngle = nDivAngle + speed end

    if keys['Q'] and speed > 0.001 then speed = speed - 0.001 end
    if keys['W'] and speed < 0.1 then speed = speed + 0.001 end
    
    if keys['Up']   then maxBranches = maxBranches + 0.1 end
    if keys['Down'] then maxBranches = maxBranches - 0.1 end
    if keys['C'] then print("Number of branches: " .. numBranches) end
end