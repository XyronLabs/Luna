local currentLine = 0

function setup()
    size(1024, 768, "Luna rainbow test")
end

function render()
    color(hue(currentLine / height))
    line(0, currentLine, width, currentLine)
    line(0, currentLine - 1, width, currentLine - 1)

    currentLine = (currentLine % height) + 1
end