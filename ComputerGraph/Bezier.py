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

# 线性bezier
def one_bezier(x, y, t):
    return (1 - t) * x + t * y

# n 次bezier曲线
# data——数据，n——阶数，k——索引
def n_bezier(data, n, k, t):
    if n == 1:
        return one_bezier(data[k], data[k+1], t)
    else:
        return (1 - t) * n_bezier(data, n-1, k, t) + t * n_bezier(data, n-1, k+1, t)


def bezier(xs, ys, num, b_xs, b_ys):
    n = len(xs) - 1
    t_step = 1.0 / (num - 1)
    t_list = np.arange(0.0, 1 + t_step, t_step)
    for t in t_list:
        b_xs.append(n_bezier(xs, n, 0, t))
        b_ys.append(n_bezier(ys, n, 0, t))


def main():
    # 六边形六个顶点
    polygon = [50, 20, 90, 20, 120, 70, 90, 120, 50, 120, 20, 70]

    x_ticks = np.arange(0, 130, 10)
    y_ticks = np.arange(0, 130, 10)
    plt.xlim(0, 130)		# 设置坐标轴范围
    plt.ylim(0, 130)
    plt.xticks(x_ticks)		# 设置坐标轴刻度
    plt.yticks(y_ticks)
    plt.axis('equal')		# 社会横纵坐标轴刻度间隔相等

    draw(polygon, 'black')  # 画原凸六边形

    points_x, points_y = [], []
    for i in range(0, 11, 2):			# 横纵坐标分离
        points_x.append(polygon[i])
        points_y.append(polygon[i+1])
    # 除了六个顶点，还有要把第一个顶点添加到最后
    points_x.append(50)     
    points_y.append(20)

    num = 100
    b_xs, b_ys = [], []
    bezier(points_x, points_y, num, b_xs, b_ys)
    plt.plot(b_xs, b_ys)
    plt.show()


if __name__ == "__main__":
    main()