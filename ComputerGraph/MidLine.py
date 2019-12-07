import turtle


def drawpixel(x, y, color='black'):
    turtle.pencolor(color)
    turtle.up()
    turtle.goto(x, y)
    turtle.dot(3)

'''
Mid point algorithm
根据交点和中点的位置来选取下一个点
'''
def MidPointLine(x0, y0, x1, y1):
    a = y0 - y1
    b = x1 - x0
    d = 2 * a + b  # 为摆脱小数，把 d0 = a + 0.5b 乘以2
    d1 = 2 * a          # d >= 0 的增量
    d2 = 2 * (a + b)    # d < 0 的增量
    x, y = x0, y0
    drawpixel(x, y)
    while x < x1:
        if d < 0:       # M在Q的下方，所以选取右上方像素
            x += 1
            y += 1
            d += d2
        else:           # M在Q的上方，所以选取右边像素
            x += 1
            d += d1
        drawpixel(x, y)


def main():
    x0 = int(input("x0: "))
    y0 = int(input("y0: "))
    x1 = int(input("x1: "))
    y1 = int(input("y1: "))
    turtle.hideturtle()
    turtle.speed(10)
    MidPointLine(x0, y0, x1, y1)
    turtle.done()


if __name__ == "__main__":
    main()
