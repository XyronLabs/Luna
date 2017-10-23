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

    __mul = function(self, other)
        local newdata = {}
        -- Scalar multiplication
        if type(other) == 'number' then
            for k, v in pairs(self) do
                newdata[k] = other * self[k]
            end
        end
        return vector:new(newdata)
    end,

    __div = function(self, other)
        local newdata = {}
        -- Scalar division
        if type(other) == 'number' then
            for k, v in pairs(self) do
                newdata[k] = other / self[k]
            end
        end
        return vector:new(newdata)
    end,

    __len = function(self)
        local sqsum = 0
        for k, v in pairs(self) do
            sqsum = sqsum + v * v
        end

        return math.sqrt(sqsum)
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

function vector:add(other)
    for k, v in pairs(self) do
        self[k] = v + other[k]
    end
    return self
end

function vector:sub(other)
    for k, v in pairs(self) do
        self[k] = v - other[k]
    end
    return self
end

function vector:mul(factor)
    for k, v in pairs(self) do
        self[k] = v * factor
    end
    return self
end

function vector:div(factor)
    for k, v in pairs(self) do
        self[k] = v / factor
    end
    return self
end