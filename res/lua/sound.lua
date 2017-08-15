--[[ Sound class ]]--
sound = {}
local sound_mt = { __index = sound }

--[[ Constructor ]]--
function sound:new(dat)
    local obj = {}
    obj.id = 'sound_' .. math.random()
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.path = obj.path or nil

    setmetatable(obj, sound_mt)
    registerObject(obj.id, 'sound', obj.path)
    return obj
end

--[[ Play/Pause ]]--
function sound:play()
    editObject(self.id, 'play')
end

function sound:pause()
    editObject(self.id, 'pause')
end

function sound:stop()
    editObject(self.id, 'stop')
end

function sound:setVolume(volume)
    editObject(self.id, 'volume', volume)
end