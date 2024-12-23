import matplotlib.pyplot as plt
from matplotlib.patches import Polygon, Rectangle
from tkinter import Tk, filedialog, Button, Label, StringVar, OptionMenu

# Чтение данных из файла
def read_input(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()
    n = int(lines[0])
    segments = [tuple(map(float, line.split())) for line in lines[1:n + 1]]
    clip_window = tuple(map(float, lines[n + 1].split()))
    return segments, clip_window

# Алгоритм средней точки для отсечения отрезков
def midpoint_clip(segment, window):
    x_min, y_min, x_max, y_max = window
    x1, y1, x2, y2 = segment

    def inside(x, y):
        return x_min <= x <= x_max and y_min <= y <= y_max

    if inside(x1, y1) and inside(x2, y2):
        return [(x1, y1), (x2, y2)]

    mid_x, mid_y = (x1 + x2) / 2, (y1 + y2) / 2
    if abs(x1 - x2) < 1e-5 and abs(y1 - y2) < 1e-5:  # Базовый случай для рекурсии
        return []

    if inside(mid_x, mid_y):
        return midpoint_clip((x1, y1, mid_x, mid_y), window) + midpoint_clip((mid_x, mid_y, x2, y2), window)
    return midpoint_clip((x1, y1, mid_x, mid_y), window) + midpoint_clip((mid_x, mid_y, x2, y2), window)

# Алгоритм Сазерленда-Ходжмана для отсечения выпуклого многоугольника
def sutherland_hodgman(polygon, window):
    x_min, y_min, x_max, y_max = window

    def clip_edge(points, edge_fn):
        clipped = []
        for i in range(len(points)):
            p1, p2 = points[i - 1], points[i]
            if edge_fn(p2):
                if not edge_fn(p1):
                    clipped.append(intersection(p1, p2, edge_fn))
                clipped.append(p2)
            elif edge_fn(p1):
                clipped.append(intersection(p1, p2, edge_fn))
        return clipped

    def intersection(p1, p2, edge_fn):
        x1, y1, x2, y2 = *p1, *p2
        if edge_fn == left:
            t = (x_min - x1) / (x2 - x1)
            return x_min, y1 + t * (y2 - y1)
        elif edge_fn == right:
            t = (x_max - x1) / (x2 - x1)
            return x_max, y1 + t * (y2 - y1)
        elif edge_fn == bottom:
            t = (y_min - y1) / (y2 - y1)
            return x1 + t * (x2 - x1), y_min
        elif edge_fn == top:
            t = (y_max - y1) / (y2 - y1)
            return x1 + t * (x2 - x1), y_max

    left = lambda p: p[0] >= x_min
    right = lambda p: p[0] <= x_max
    bottom = lambda p: p[1] >= y_min
    top = lambda p: p[1] <= y_max

    edges = [left, right, bottom, top]
    clipped_polygon = polygon[:]
    for edge_fn in edges:
        clipped_polygon = clip_edge(clipped_polygon, edge_fn)
    return clipped_polygon

# Визуализация результата
def visualize(segments, clipped_segments, polygon, clipped_polygon, clip_window):
    print("Polygon data:", polygon)  # Debug output
    fig, ax = plt.subplots()
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)

    # Отображение окна отсечения
    x_min, y_min, x_max, y_max = clip_window
    ax.add_patch(Rectangle((x_min, y_min), x_max - x_min, y_max - y_min,
                           edgecolor='blue', fill=False))

    # Отображение исходных данных
    for segment in segments:
        x1, y1, x2, y2 = segment
        ax.plot([x1, x2], [y1, y2], 'r-', label="Исходный отрезок")

    # Видимые части отрезков
    for segment in clipped_segments:
        if segment:
            x1, y1, x2, y2 = segment[0][0], segment[0][1], segment[1][0], segment[1][1]
            ax.plot([x1, x2], [y1, y2], 'g-', label="Видимый отрезок")

    # Многоугольники
    if polygon:  # Проверка на пустоту полигональных данных
        polygon_patch = Polygon(polygon, closed=True, fill=None, edgecolor='purple')
        ax.add_patch(polygon_patch)

    if clipped_polygon:  # Проверка на пустоту отсечённого полигона
        clipped_polygon_patch = Polygon(clipped_polygon, closed=True, fill=None, edgecolor='green')
        ax.add_patch(clipped_polygon_patch)

    plt.show()

# Окно выбора алгоритма и файла
def main():
    def open_file():
        file_path.set(filedialog.askopenfilename(filetypes=[("Text files", "*.txt")]))

    def run():
        if not file_path.get():
            print("Не выбран файл")
            return

        segments, clip_window = read_input(file_path.get())

        if algo_var.get() == "Midpoint":
            clipped_segments = [midpoint_clip(segment, clip_window) for segment in segments]
            polygon, clipped_polygon = [], []
        elif algo_var.get() == "Sutherland-Hodgman":
            polygon = [(0, 0), (5, 0), (5, 5), (0, 5)]
            clipped_polygon = sutherland_hodgman(polygon, clip_window)
            clipped_segments = []
        else:
            print("Не выбран алгоритм")
            return

        visualize(segments, clipped_segments, polygon, clipped_polygon, clip_window)

    root = Tk()
    root.title("Визуализация отсечения")

    file_path = StringVar()
    algo_var = StringVar(value="Выберите алгоритм")

    Label(root, text="Выберите файл:").grid(row=0, column=0, padx=10, pady=10)
    Button(root, text="Открыть", command=open_file).grid(row=0, column=1, padx=10, pady=10)

    Label(root, text="Выберите алгоритм:").gr
