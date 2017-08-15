--[[ Color format: RGBA ]]--
colors = {
    ["black"]       = 0x000000ff,
    ["white"]       = 0xffffffff,
    ["red"]         = 0xff0000ff,
    ["green"]       = 0x00ff00ff,
    ["blue"]        = 0x0000ffff,
    ["yellow"]      = 0xffff00ff,
    ["magenta"]     = 0xff00ffff,
    ["cyan"]        = 0x00ffffff,
    ["transparent"] = 0x00000000,
}

function hsva(h, s, v, a)
    local r, g, b = 0, 0, 0
    local var_r, var_g, var_b, var_h, var_i = 0, 0, 0, 0, 0

    if s == 0 then
        r, g, b, a = math.floor(v * 255), math.floor(v * 255), math.floor(v * 255), math.floor(a * 255)
    else
        var_h = h * 6
        if var_h == 6 then var_h = 0 end

        var_i = math.floor(var_h)
        var_1 = v * (1 - s)
        var_2 = v * (1 - s * (var_h - var_i))
        var_3 = v * (1 - s * (1 - (var_h - var_i)))

        if     var_i == 0 then var_r, var_g, var_b = v    , var_3, var_1
        elseif var_i == 1 then var_r, var_g, var_b = var_2, v    , var_1
        elseif var_i == 2 then var_r, var_g, var_b = var_1, v    , var_3
        elseif var_i == 3 then var_r, var_g, var_b = var_1, var_2, v    
        elseif var_i == 4 then var_r, var_g, var_b = var_3, var_1, v    
        else                   var_r, var_g, var_b = v    , var_1, var_2
        end

        r, g, b, a = math.floor(var_r * 255), math.floor(var_g * 255), math.floor(var_b * 255), math.floor(a * 255)
    end

    return bit32.lshift(r, 24) + bit32.lshift(g, 16) + bit32.lshift(b, 8) + a
end

function hsv(h, s, v)
    return hsva(h, s, v, 1)
end

function hue(h)
    return hsva(h, 1, 1, 1)
end