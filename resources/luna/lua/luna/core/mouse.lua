local _mousekeys = {
    [0] = "Left",
    "Right",
    "Middle",
    "Xbutton1",
    "Xbutton2",
    "ButtonCount"
}

mousekeys = {}

for k, v in pairs(_mousekeys) do
	mousekeys[v] = false
end

function pressMouseKey(k)
	mousekeys[_mousekeys[k]] = true
end

function releaseMouseKey(k)
	mousekeys[_mousekeys[k]] = false
end