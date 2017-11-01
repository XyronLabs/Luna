simplemap = {}

function simplemap:new(dat)
    local obj = dat or {}

    obj.map = {}

    setmetatable(obj, { __index = simplemap })
    return obj
end

function simplemap:loadMap(path)
    local l = 1
    for line in io.lines(path) do
        self.map[l] = {}
        for i = 1, #line do
            self.map[l][i] = line:sub(i, i)
        end
        l = l + 1
    end
end

function simplemap:render()
    for y = 1, #self.map do
        for x = 1, #self.map[y] do
            if self.map[y][x] == 'o' then
                color(colors.red)
            else
                color(colors.black)
            end
            rect(x * 10, y * 10, 10, 10)
        end
    end
end