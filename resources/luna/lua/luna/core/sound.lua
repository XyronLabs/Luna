--[[ Sound class ]]--
sound = {}
local sound_mt = { __index = sound }

sound.idCounter = 0

--[[ Constructor ]]--
function sound:new(dat)
    local obj = {}
    obj.id = 'sound_' .. sound.idCounter
    sound.idCounter = sound.idCounter + 1
    
    for k, v in pairs(dat) do
        obj[k] = v
    end

    obj.path = obj.path or nil

    setmetatable(obj, sound_mt)
    registerObject(obj.id, 'sound', obj.path)
    if obj.volume then obj:setVolume(obj.volume) end
    if obj.loop then obj:setLoop(obj.loop) end
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
    self.volume = volume
    editObject(self.id, 'volume', volume)
end

function sound:setLoop(loop)
    self.loop = loop
    editObject(self.id, 'loop', loop)
end