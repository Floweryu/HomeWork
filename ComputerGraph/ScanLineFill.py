import numpy as np
import matplotlib.pyplot as plt
from math import *
import turtle

class Node(object):
    def __init__(self, x = None, y = None, increment = None, ymax = None):
        self.x = x
        self.y = y
        self.increment = increment
        self.ymax = ymax
        self.next = None


class LinkList(object):
    def __init__(self, node=None):
        self.head = node


def drawpixel(x, y, color='black'):
    turtle.pencolor(color)
    turtle.up()
    turtle.goto(x, y)
    turtle.dot(3)


def main():
    polygon = [20, 20, 20, 70, 50, 50, 110, 80, 110, 30, 50, 10]
    points_x, points_y = [], []
    for i in range(0, 11, 2):			# 横纵坐标分离
        points_x.append(polygon[i])
        points_y.append(polygon[i+1])
    print(points_x)
    print(points_y)
    ymin, ymax = min(points_y), max(points_y)

    # 初始化新边表
    net = {}
    for i in range(ymin, ymax + 1):
        net[i] = []

    # 初始化各条边
    for i in range(len(points_x)):
        index1, index2 = i, (i+1) % len(points_x)
        y_min = min(points_y[index1], points_y[index2])
        y_max = max(points_y[index1], points_y[index2])
        if y_max == points_y[index1]:
            x2 = points_x[index1]
            x1 = points_x[index2]
        else:
            x2 = points_x[index2]
            x1 = points_x[index1]
        # 增量计算都是： 坐标点y值大的对应的x2 减去坐标点y值小的对应的x1
        increment = (x2 - x1) / (y_max - y_min)
        # 根据底顶点的y值来建立net表的索引
        net[y_min].append(Node(x1, y_min, increment, y_max))    # y值小的对应点添加到表中
        # 输出每条扫描线的新边表
        for j in range(len(net[y_min])):
            print("edge:",net[y_min][j].x, net[y_min][j].increment, net[y_min][j].ymax)
    
    # 建立活性边表
    aet = LinkList(Node())
    for y in range(ymin, ymax + 1):
        print("扫描线:   " , y)
        for i in range(len(net[y])):    # 遍历每一条扫描线经过的活性边
            data = net[y][i]
            head_node = aet.head
            if head_node.next == None:  # 为空，就直接插入
                head_node.next = data
            else:       # 按x递增的顺序插入到表中
                while data.x > head_node.next.x:     # 遍历链表找到可以插入的位置(插在比data.x大的节点前)
                    head_node = head_node.next
                data.next = head_node.next           # 插入节点 data
                head_node.next = data
        
        # 遍历AET表，寻找填充区间
        fill_points = []
        head_node = aet.head
        while head_node.next != None:
            ymin = head_node.next.y
            ymax = head_node.next.ymax
            if y > ymin and y <= ymax:
                fill_points.append(head_node.next.x)
            elif y == ymin and y < ymax:
                fill_points.append(head_node.next.x)
                fill_points.append(head_node.next.x)

            head_node = head_node.next
        fill_points = sorted(fill_points)

        # 进行填充
        for i in range(0, len(fill_points), 2):
            # print("length: ", len(fill_points))
            x1, x2 = fill_points[i], fill_points[i+1]
            for x in range(int(x1), int(x2)):
                drawpixel(x, y)
        # 遍历aet进行测试
        head_node = aet.head
        while head_node != None:
            head_node = head_node.next
        
        # 遍历aet，把ymax = y的节点从aet删除，并把ymax > i结点的x值递增increment
        head_node = aet.head
        while head_node.next != None:
            if head_node.next.ymax == y:
                head_node.next = head_node.next.next
            else:
                head_node.next.x = head_node.next.x + head_node.next.increment
                head_node = head_node.next

if __name__ == "__main__":
    turtle.hideturtle()
    turtle.speed(10)
    turtle.screensize(600, 400, 'red')
    main()
    turtle.mainloop()
