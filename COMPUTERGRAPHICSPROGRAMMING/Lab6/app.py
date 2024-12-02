import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class Object3D:
    def __init__(self, vertices, edges):
        self.vertices = np.array(vertices)
        self.edges = edges

    def transform(self, matrix):
        homogenous_vertices = np.hstack((self.vertices, np.ones((self.vertices.shape[0], 1))))
        transformed_vertices = np.dot(homogenous_vertices, matrix.T)
        self.vertices = transformed_vertices[:, :3]
        return matrix

    def plot(self, ax, color='blue', show_vertices=True):
        for edge in self.edges:
            x = [self.vertices[edge[0]][0], self.vertices[edge[1]][0]]
            y = [self.vertices[edge[0]][1], self.vertices[edge[1]][1]]
            z = [self.vertices[edge[0]][2], self.vertices[edge[1]][2]]
            ax.plot(x, y, z, color=color)

        if show_vertices:
            ax.scatter(self.vertices[:, 0], self.vertices[:, 1], self.vertices[:, 2], color='red')


vertices = [
    [0, 0, 0], [0, 1, 0], [0.2, 1, 0], [0.2, 0.2, 0], [0.6, 0.2, 0], [0.6, 1, 0], [0.8, 1, 0], [0.8, 0, 0],
    [0, 0, 1], [0, 1, 1], [0.2, 1, 1], [0.2, 0.2, 1], [0.6, 0.2, 1], [0.6, 1, 1], [0.8, 1, 1], [0.8, 0, 1]
]

edges = [
    [0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 0],  # Лицевая грань
    [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15], [15, 8],  # Задняя грань
    [0, 8], [1, 9], [2, 10], [3, 11], [4, 12], [5, 13], [6, 14], [7, 15]  # Рёбра между гранями
]

letter_ch = Object3D(vertices, edges)


def scale_matrix(sx, sy, sz):
    return np.array([
        [sx, 0, 0, 0],
        [0, sy, 0, 0],
        [0, 0, sz, 0],
        [0, 0, 0, 1]
    ])


def translate_matrix(tx, ty, tz):
    return np.array([
        [1, 0, 0, tx],
        [0, 1, 0, ty],
        [0, 0, 1, tz],
        [0, 0, 0, 1]
    ])


def rotate_matrix_x(angle):
    c, s = np.cos(angle), np.sin(angle)
    return np.array([
        [1, 0, 0, 0],
        [0, c, -s, 0],
        [0, s, c, 0],
        [0, 0, 0, 1]
    ])


def rotate_matrix_y(angle):
    c, s = np.cos(angle), np.sin(angle)
    return np.array([
        [c, 0, s, 0],
        [0, 1, 0, 0],
        [-s, 0, c, 0],
        [0, 0, 0, 1]
    ])


def rotate_matrix_z(angle):
    c, s = np.cos(angle), np.sin(angle)
    return np.array([
        [c, -s, 0, 0],
        [s, c, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1]
    ])


def plot_projections_with_edges(obj):
    fig, axs = plt.subplots(1, 3, figsize=(18, 6))

    for edge in obj.edges:
        x = [obj.vertices[edge[0]][0], obj.vertices[edge[1]][0]]
        y = [obj.vertices[edge[0]][1], obj.vertices[edge[1]][1]]
        axs[0].plot(x, y, color='blue')
    axs[0].scatter(obj.vertices[:, 0], obj.vertices[:, 1], color='red')  # Вершины
    axs[0].set_title("Проекция на плоскость Oxy")
    axs[0].set_xlabel("X")
    axs[0].set_ylabel("Y")
    axs[0].grid()

    for edge in obj.edges:
        x = [obj.vertices[edge[0]][0], obj.vertices[edge[1]][0]]
        z = [obj.vertices[edge[0]][2], obj.vertices[edge[1]][2]]
        axs[1].plot(x, z, color='green')
    axs[1].scatter(obj.vertices[:, 0], obj.vertices[:, 2], color='red')  # Вершины
    axs[1].set_title("Проекция на плоскость Oxz")
    axs[1].set_xlabel("X")
    axs[1].set_ylabel("Z")
    axs[1].grid()

    for edge in obj.edges:
        y = [obj.vertices[edge[0]][1], obj.vertices[edge[1]][1]]
        z = [obj.vertices[edge[0]][2], obj.vertices[edge[1]][2]]
        axs[2].plot(y, z, color='red')
    axs[2].scatter(obj.vertices[:, 1], obj.vertices[:, 2], color='red')  # Вершины
    axs[2].set_title("Проекция на плоскость Oyz")
    axs[2].set_xlabel("Y")
    axs[2].set_ylabel("Z")
    axs[2].grid()

    plt.tight_layout()
    plt.show()


fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(111, projection='3d')
letter_ch.plot(ax)
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
plt.title("3D-модель буквы 'С'")
plt.show()

scale = letter_ch.transform(scale_matrix(1.5, 1.5, 1.5))
translate = letter_ch.transform(translate_matrix(1, 1, 0))
rotate = letter_ch.transform(rotate_matrix_z(np.pi / 4))

print("Итоговая матрица преобразований:")
print(rotate)

plot_projections_with_edges(letter_ch)
