simplemap = {}

simplemap.colors = {
    ["o"] = colors.black,
    ["w"] = colors.white,
    ["r"] = colors.red,
    ["g"] = colors.green,
    ["b"] = colors.blue,
    ["y"] = colors.yellow,
    ["m"] = colors.magenta,
    ["c"] = colors.cyan,
    ["t"] = colors.transparent
}

function simplemap:new(dat)
    local obj = dat or {}

    obj.map = {}
    obj.scale = obj.scale or 10

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
            if simplemap.colors[ self.map[y][x] ] then
                color(simplemap.colors[ self.map[y][x] ])
            else
                log(loglevel.FATAL, self.map[y][x] .. " is not a color!")
            end
            rect( (x - 1) * self.scale, (y - 1) * self.scale, self.scale, self.scale)
        end
    end
end