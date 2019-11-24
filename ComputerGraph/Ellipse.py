import turtle

# 设置画笔
def drawpixel(x, y):
    turtle.penup()
    turtle.goto(x, y)
    turtle.dot(3)


def ellipse(a, b):
    x, y = 0, b
    d1 = b * b + a * a * (-b + 0.25)
    drawpixel(x, y)
    while b * b * (x + 1) < a * a * (y - 0.5):
        if d1 < 0:
            d1 += b * b * (2 * x + 3)
            x += 1
        else:
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2)
            y -= 1
            x += 1
        drawpixel(x, y)
        drawpixel(x, -y)
        drawpixel(-x, y)
        drawpixel(-x, -y)

    d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b
    while y > 0:
        if d2 < 0:
            d2 += b * b * (2 * x + 2) + a * a * (-y + 3)
            x += 1
            y -= 1
        else:
            d2 += a * a * (-2 * y + 3)
            y -= 1
        drawpixel(x, y)
        drawpixel(x, -y)
        drawpixel(-x, y)
        drawpixel(-x, -y)


def main():
    a = int(input("Please input the long radius:"))
    b = int(input("Please input the short radius:"))
    turtle.pencolor('red')
    turtle.hideturtle()
    turtle.speed(50)
    turtle.screensize(800, 600, 'white')
    ellipse(a, b)
    turtle.done()

if __name__ == '__main__':
    main()
