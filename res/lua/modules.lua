package.path = package.path .. ";./res/lua/luna/?.lua;./res/lua/extensions/?/init.lua;"
                            .. "/usr/local/luna/res/lua/luna/?.lua;/usr/local/luna/res/lua/extensions/?/init.lua;"
                            .. "C:/Program Files (x86)/XyronLabs/Luna/res/lua/luna/?.lua;C:/Program Files (x86)/XyronLabs/Luna/res/lua/extensions/?/init.lua"

--[[ Load luna variables ]]--
luna = {}
luna.version = "0.6.1"
luna = setmetatable({}, { __index = luna, __newindex = function() error("luna table is read-only") end })

--[[ Load core modules ]]--
require 'core.rectangleShape'
require 'core.ellipseShape'
require 'core.customShape'
require 'core.keys'
require 'core.sound'
require 'core.colors'
require 'core.textbox'
require 'core.mouse'
require 'core.log'