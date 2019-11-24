from math import *
import numpy as np
import matplotlib.pyplot as plt

# 绘图函数
def draw(points, color):
	points_x, points_y = [], []
	for i in range(0, 11, 2):			# 横纵坐标分离
		points_x.append(points[i])
		points_y.append(points[i+1])
	x, y = [-1, -1], [-1, -1]
	for i in range(0, 5):
		x[0] = points_x[i]
		x[1] = points_x[i+1]
		y[0] = points_y[i]
		y[1] = points_y[i+1]
		plt.plot(x, y, color)
	plt.plot([points_x[5], points_x[0]], [points_y[5], points_y[0]], color)

# 旋转函数——angle：角度；rotate_x, rotate_y：绕点坐标
def rotate(points, angle, rotate_x, rotate_y):
    for i in range(0, 11, 2):  # 遍历 0 ~ 10，只取偶数位置即 x 值
        temp = points[i]
        points[i] = round((points[i] - rotate_x) * cos(radians(angle))
                        - (points[i + 1] - rotate_y) * sin(radians(angle))
                        + rotate_x)
        points[i + 1] = round((temp - rotate_x) * sin(radians(angle))
                        + (points[i + 1] - rotate_x) * cos(radians(angle))
                        + rotate_y)
    return points

# 六边形六个顶点
polygon = [50, 20, 90, 20, 120, 70, 90, 120, 50, 120, 20, 70]

x_ticks = np.arange(0, 130, 10)
y_ticks = np.arange(0, 130, 10)
plt.xlim(0, 130)		# 设置坐标轴范围
plt.ylim(0, 130)
plt.xticks(x_ticks)		# 设置坐标轴刻度
plt.yticks(y_ticks)
plt.axis('equal')		# 社会横纵坐标轴刻度间隔相等

draw(polygon, 'black')	# 画原凸六边形

rotate_polygon = rotate(polygon, 45, 70, 70)	# 绕点旋转45度

draw(rotate_polygon, 'red')		# 画旋转后的凸六边形
plt.scatter([70], [70])		# 画出旋转点
plt.show()
