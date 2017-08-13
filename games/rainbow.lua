local currentLine = 0

function setup()
    size(1024, 768, "Luna rainbow test")
end

function render()
    color(hsva(currentLine / height, 1, 1, 1))
    line(0, currentLine, width, currentLine)

    currentLine = (currentLine % height) + 1
end