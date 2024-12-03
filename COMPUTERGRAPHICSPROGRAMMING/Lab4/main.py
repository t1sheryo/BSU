import tkinter as tk
from tkinter import ttk, Canvas
import math

def step_by_step(x1, y1, x2, y2, canvas):
    dx, dy = x2 - x1, y2 - y1
    steps = max(abs(dx), abs(dy))
    x_inc, y_inc = dx / steps, dy / steps
    x, y = x1, y1

    for _ in range(steps + 1):
        canvas.create_oval(x, y, x + 1, y + 1, fill="black")
        x += x_inc
        y += y_inc

def dda(x1, y1, x2, y2, canvas):
    step_by_step(x1, y1, x2, y2, canvas)  # DDA совпадает с пошаговым

def bresenham_line(x1, y1, x2, y2, canvas):
    dx, dy = abs(x2 - x1), abs(y2 - y1)
    sx, sy = (1 if x2 > x1 else -1), (1 if y2 > y1 else -1)
    err = dx - dy

    while True:
        canvas.create_oval(x1, y1, x1 + 1, y1 + 1, fill="black")
        if x1 == x2 and y1 == y2:
            break
        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x1 += sx
        if e2 < dx:
            err += dx
            y1 += sy

def bresenham_circle(cx, cy, r, canvas):
    x, y, p = 0, r, 3 - 2 * r
    while x <= y:
        for point in [(cx + x, cy + y), (cx - x, cy + y), (cx + x, cy - y), (cx - x, cy - y),
                      (cx + y, cy + x), (cx - y, cy + x), (cx + y, cy - x), (cx - y, cy - x)]:
            canvas.create_oval(point[0], point[1], point[0] + 1, point[1] + 1, fill="black")
        if p < 0:
            p += 4 * x + 6
        else:
            p += 4 * (x - y) + 10
            y -= 1
        x += 1

def draw_algorithm():
    x1 = int(entry_x1.get())
    y1 = int(entry_y1.get())
    x2 = int(entry_x2.get())
    y2 = int(entry_y2.get())
    algorithm = combo_algorithm.get()
    canvas.delete("all")
    if algorithm == "Пошаговый алгоритм":
        step_by_step(x1, y1, x2, y2, canvas)
    elif algorithm == "ЦДА":
        dda(x1, y1, x2, y2, canvas)
    elif algorithm == "Брезенхем (отрезок)":
        bresenham_line(x1, y1, x2, y2, canvas)
    elif algorithm == "Брезенхем (окружность)":
        r = int(entry_radius.get())
        bresenham_circle(x1, y1, r, canvas)
    elif algorithm == "Кастла-Питвея (кривая)":
        points = parse_control_points(entry_control_points.get())
        if points:
            draw_casteljau(points, canvas)
        else:
            print("Ошибка: некорректные контрольные точки.")
    elif algorithm == "Сглаживание Ву":
        wu_line(x1, y1, x2, y2, canvas)



def casteljau(points, t):
    if len(points) == 1:
        return points[0]
    new_points = [
        ((1 - t) * p1[0] + t * p2[0], (1 - t) * p1[1] + t * p2[1])
        for p1, p2 in zip(points[:-1], points[1:])
    ]
    return casteljau(new_points, t)


def draw_casteljau(control_points, canvas):
    canvas.delete("all")
    steps = 100
    for i in range(steps):
        t1 = i / steps
        t2 = (i + 1) / steps
        p1 = casteljau(control_points, t1)
        p2 = casteljau(control_points, t2)
        canvas.create_line(p1[0], p1[1], p2[0], p2[1], fill="black")

def parse_control_points(entry):
    """Парсинг точек из строки."""
    try:
        return [tuple(map(int, point.split(','))) for point in entry.split(';')]
    except ValueError:
        return None

def wu_line(x1, y1, x2, y2, canvas):
    def plot(x, y, c):
        intensity = int(255 * (1 - c))
        color = f"#{intensity:02x}{intensity:02x}{intensity:02x}"
        canvas.create_oval(x, y, x + 1, y + 1, outline=color, fill=color)

    def fpart(x):
        return x - int(x)

    def rfpart(x):
        return 1 - fpart(x)

    steep = abs(y2 - y1) > abs(x2 - x1)
    if steep:
        x1, y1 = y1, x1
        x2, y2 = y2, x2
    if x1 > x2:
        x1, x2 = x2, x1
        y1, y2 = y2, y1

    dx = x2 - x1
    dy = y2 - y1
    gradient = dy / dx if dx != 0 else 1

    xend = round(x1)
    yend = y1 + gradient * (xend - x1)
    xgap = rfpart(x1 + 0.5)
    xpxl1 = xend
    ypxl1 = int(yend)
    if steep:
        plot(ypxl1, xpxl1, rfpart(yend) * xgap)
        plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap)
    else:
        plot(xpxl1, ypxl1, rfpart(yend) * xgap)
        plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap)
    intery = yend + gradient

    xend = round(x2)
    yend = y2 + gradient * (xend - x2)
    xgap = fpart(x2 + 0.5)
    xpxl2 = xend
    ypxl2 = int(yend)
    if steep:
        plot(ypxl2, xpxl2, rfpart(yend) * xgap)
        plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap)
    else:
        plot(xpxl2, ypxl2, rfpart(yend) * xgap)
        plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap)

    for x in range(xpxl1 + 1, xpxl2):
        if steep:
            plot(int(intery), x, rfpart(intery))
            plot(int(intery) + 1, x, fpart(intery))
        else:
            plot(x, int(intery), rfpart(intery))
            plot(x, int(intery) + 1, fpart(intery))
        intery += gradient


root = tk.Tk()
root.title("Растровые алгоритмы")
root.geometry("800x600")

frame = tk.Frame(root)
frame.pack(pady=10)

# Поля ввода
tk.Label(frame, text="x1:").grid(row=0, column=0)
entry_x1 = tk.Entry(frame)
entry_x1.grid(row=0, column=1)

tk.Label(frame, text="y1:").grid(row=0, column=2)
entry_y1 = tk.Entry(frame)
entry_y1.grid(row=0, column=3)

tk.Label(frame, text="x2:").grid(row=1, column=0)
entry_x2 = tk.Entry(frame)
entry_x2.grid(row=1, column=1)

tk.Label(frame, text="y2:").grid(row=1, column=2)
entry_y2 = tk.Entry(frame)
entry_y2.grid(row=1, column=3)

tk.Label(frame, text="Радиус:").grid(row=2, column=0)
entry_radius = tk.Entry(frame)
entry_radius.grid(row=2, column=1)

tk.Label(frame, text="Контрольные точки:").grid(row=4, column=0)
entry_control_points = tk.Entry(frame, width=40)
entry_control_points.grid(row=4, column=1, columnspan=2)


# Выбор алгоритма
combo_algorithm = ttk.Combobox(frame, values=[
    "Пошаговый алгоритм",
    "ЦДА",
    "Брезенхем (отрезок)",
    "Брезенхем (окружность)",
    "Кастла-Питвея (кривая)",
    "Сглаживание Ву"
])
combo_algorithm.grid(row=3, column=1)
combo_algorithm.set("Пошаговый алгоритм")  # Установить алгоритм по умолчанию

# Кнопка "Построить"
draw_button = tk.Button(frame, text="Построить", command=draw_algorithm)
draw_button.grid(row=3, column=2)

# Холст для рисования
canvas = Canvas(root, width=800, height=400, bg="white")
canvas.pack()

root.mainloop()