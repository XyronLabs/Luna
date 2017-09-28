vector = {}
local vector_mt = {
    __index = vector,
    __add = function(self, other)
        local newdata = {}
        for k, v in pairs(self) do
            newdata[k] = v + other[k]
        end
        return vector:new(newdata)
    end,
    __sub = function(self, other)
        local newdata = {}
        for k, v in pairs(self) do
            newdata[k] = v - other[k]
        end
        return vector:new(newdata)
    end,
    __tostring = function(self)
        local str = "("
        for k, v in pairs(self) do
            str = str .. k .. "=" .. v .. ","
        end
        return str:sub(1, #str-1) .. ")"
    end
}

function vector:new(...)
    local obj = {}

    local args = { ... }
    if #args == 1 then
        obj = ...
    elseif #args == 2 then
        obj.x, obj.y = args[1], args[2]
    elseif #args == 3 then
        obj.x, obj.y, obj.z = args[1], args[2], args[3]
    else
        error("Error in vector arguments constructor")
    end

    setmetatable(obj, vector_mt)
    return obj
end