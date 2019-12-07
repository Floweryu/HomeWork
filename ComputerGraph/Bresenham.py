import turtle


def drawpixel(x, y, color='black'):
    turtle.pencolor(color)
    turtle.up()
    turtle.goto(x, y)
    turtle.dot(3)


'''
Bresenham algorithm
根据增量是否超过1来选取下一点
'''
def BresenhamLine(x0, y0, x1, y1):
    k = (y1 - y0) / (x1 - x0)
    e = -0.5
    x, y = x0, y0
    for i in range(0, x1 - x0):
        drawpixel(x, y)
        x += 1      # x 总是要向前移动
        e += k      # e 的增量
        if e >= 0:      # 增量大于 0 后，y 加一，同时增量在 [0, 1]之间
            y += 1
            e -= 1
        drawpixel(x, y)



def main():
    x0 = int(input("x0: "))
    y0 = int(input("y0: "))
    x1 = int(input("x1: "))
    y1 = int(input("y1: "))
    turtle.hideturtle()
    turtle.speed(10)
    BresenhamLine(x0, y0, x1, y1)
    turtle.done()


if __name__ == "__main__":
    main()
