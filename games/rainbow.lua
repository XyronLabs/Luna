local currentLine = 0

function setup()
    size(1024, 768, "Luna rainbow test")
end

function render()
    print(currentLine)
    if currentLine >= height then return end

    color(hsva(currentLine / height, 1, 1, 1))
    line(0, currentLine, width, currentLine)
    line(0, currentLine - 1, width, currentLine - 1)

    currentLine = (currentLine % height) + 1
end