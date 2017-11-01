simplemap = {}

function simplemap:new(dat)
    local obj = dat or {}

    obj.map = {}

    setmetatable(obj, { __index = simplemap })
    return obj
end

function loadMap(path)
end

function render()
end