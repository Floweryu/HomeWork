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


# 六边形六个顶点
polygon = [2, 2, 5, 1, 11, 3, 11, 8, 5, 5, 2, 7]

x_ticks = np.arange(0, 13, 1)
y_ticks = np.arange(0, 10, 1)
plt.xlim(0, 13)		# 设置坐标轴范围
plt.ylim(0, 10)
plt.xticks(x_ticks)		# 设置坐标轴刻度
plt.yticks(y_ticks)

draw(polygon, 'black')  # 画原凸六边形
plt.show()
