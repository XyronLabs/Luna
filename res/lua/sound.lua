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
    addSound(obj.id, obj.path)
    return obj
end

--[[ Play/Pause ]]--
function sound:play()
    playSound(self.id)
end

function sound:pause()
    pauseSound(self.id)
end

function sound:stop()
    stopSound(self.id)
end