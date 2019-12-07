import turtle

def drawpixel(x, y, color='black'):
    turtle.pencolor(color)
    turtle.up()
    turtle.goto(x, y)
    turtle.dot(3)


'''
DDA line algorithm
仅适用于 |k|<=1的情形，在这种情况下，x每增加 1，y最多增加 1
当|k|>1时，y 每增加1，x应增加 1 / k
'''
def DDA_line(x0, y0, x1, y1):
    dx = x1 - x0
    dy = y1 - y0
    k = dy / dx
    y = y0
    for i in range(x0, x1):
        drawpixel(i, int(y + 0.5))  # y + 0.5 是为了取离真正交点（这里就是y)近的像素网格点作为光栅后的点(也可四舍五入)
        y = y + k       # x 每递增1，y递增k


def main():
    x0 = int(input("x0: "))
    y0 = int(input("y0: "))
    x1 = int(input("x1: "))
    y1 = int(input("y1: "))
    turtle.hideturtle()
    turtle.speed(10)
    DDA_line(x0, y0, x1, y1)
    turtle.done()

if __name__ == "__main__":
    main()
