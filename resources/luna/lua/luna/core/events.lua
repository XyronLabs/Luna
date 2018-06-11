events = {
    ["key"] = {
        ["pressed"] = "key_pressed",
        ["released"] = "key_released"
    },
    ["text_entered"] = "text_entered",
    ["mouse"] = {
        ["button"] = {
            ["pressed"] = "mouse_button_pressed",
            ["released"] = "mouse_button_released"
        },
        ["moved"] = "mouse_moved",
        ["scrolled"] = "mouse_wheel_scrolled",
        ["left"] = "mouse_left",
        ["entered"] = "mouse_entered"
    },
    ["joystick"] = {
        ["button"] = {
            ["pressed"] = "joystick_button_pressed",
            ["released"] = "joystick_button_released"
        },
        ["moved"] = "joystick_moved",
        ["connected"] = "joystick_connected",
        ["disconnected"] = "joystick_disconnected"
    },
    ["focus"] = {
        ["lost"] = "focus_lost",
        ["gained"] = "focus_gained"
    },
    ["resized"] = "resized"
}