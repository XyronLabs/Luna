--[[ Ellipse class ]]--
configuration = {}
local configuration_mt = { __index = configuration }

--[[ Constructor ]]--
function configuration:new(path)
    local obj = {}
    obj.path = path
    obj.config = {}

    for l in io.lines(obj.path) do
        if l.sub(1, 1) ~= '#' then
            local eq = l:find("=")
            obj.config[l:sub(1, eq - 1)] = l:sub(eq + 1, #l)
        end
    end

    setmetatable(obj, configuration_mt)
    return obj
end

--[[ Render ]]--
function configuration:get(key)
    return self.config[key]
end

--[[ Setters ]]--
function configuration:set(key, value)
    self.config[key] = value
end

function configuration:save(key)
    local tmp = {}
    for l in io.lines(self.path) do
        table.insert(tmp, l)
    end

    local f = io.open(self.path, 'w')
    
    for _, v in pairs(tmp) do
        if v:find(key) then
            v = key .. "=" .. self.config[key]
        end
        f:write(v .. "\n")
    end

    f:close()
end

function configuration:saveAll()
    for k, _ in pairs(self.config) do
        self:save(k)
    end
end

function configuration:print()
    for k, v in pairs(self.config) do
        print(k .. " = " .. v)
    end
end