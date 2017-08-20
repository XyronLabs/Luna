package.path = package.path .. ";./res/lua/luna/?.lua;./res/lua/extensions/?/init.lua;"
                            .. "/usr/local/luna/res/lua/luna/?.lua;/usr/local/luna/res/lua/extensions/?/init.lua;"

require 'core.rectangleShape'
require 'core.ellipseShape'
require 'core.keys'
require 'core.sound'
require 'core.colors'
require 'core.textbox'
require 'core.mouse'
require 'core.log'