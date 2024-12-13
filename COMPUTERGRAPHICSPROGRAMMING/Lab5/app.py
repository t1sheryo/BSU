import matplotlib.pyplot as plt
from shapely.geometry import LineString, Polygon
from shapely.geometry.polygon import orient
from shapely.validation import explain_validity
from tkinter import Tk, filedialog, Button, Label, OptionMenu, StringVar

def read_input_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    n = int(lines[0])
    segments = [
        [(float(x1), float(y1)), (float(x2), float(y2))]
        for x1, y1, x2, y2 in (line.split() for line in lines[1:n + 1])
    ]
    x_min, y_min, x_max, y_max = map(float, lines[n + 1].split())
    clipping_window = [(x_min, y_min), (x_max, y_min), (x_max, y_max), (x_min, y_max), (x_min, y_min)]
    return segments, clipping_window

def validate_and_prepare_polygon(polygon):
    polygon = orient(Polygon(polygon), sign=1.0)
    if not polygon.is_valid:
        print(f"Invalid geometry: {explain_validity(polygon)}")
        polygon = polygon.buffer(0)
    return polygon

def midpoint_algorithm(segment, clipping_window):
    line = LineString(segment)
    clip_polygon = Polygon(clipping_window)
    result = line.intersection(clip_polygon)
    if result.is_empty:
        return None
    return list(result.coords)

def polygon_clip(subject_polygon_coords, clipping_window_coords):
    subject_polygon = validate_and_prepare_polygon(subject_polygon_coords)
    clipping_polygon = validate_and_prepare_polygon(clipping_window_coords)
    result = subject_polygon.intersection(clipping_polygon)
    return result if not result.is_empty else None

def draw(segments, clipping_window, clipped_segments, polygon_result):
    fig, ax = plt.subplots()

    x, y = zip(*clipping_window)
    ax.fill(x, y, alpha=0.3, color='green', label='Clipping Window')

    for segment in segments:
        x, y = zip(*segment)
        ax.plot(x, y, color='blue', label='Original Segments')

    for segment in clipped_segments:
        if segment:
            x, y = zip(*segment)
            ax.plot(x, y, color='red', label='Clipped Segments')

    if polygon_result:
        x, y = polygon_result.exterior.xy
        ax.plot(x, y, color='orange', label='Clipped Polygon')

    ax.set_xlim(0, 900)
    ax.set_ylim(0, 600)
    ax.set_aspect('equal', adjustable='box')
    ax.legend()
    plt.show()

def process_data(file_path, algorithm_choice):
    segments, clipping_window = read_input_file(file_path)
    clipped_segments = []

    if algorithm_choice == "Midpoint Algorithm":
        clipped_segments = [
            midpoint_algorithm(segment, clipping_window) for segment in segments
        ]
    elif algorithm_choice == "Polygon Clipping":
        polygon_coords = [(200, 200), (700, 200), (700, 500), (200, 500), (200, 200)]
        polygon_result = polygon_clip(polygon_coords, clipping_window)
        draw(segments, clipping_window, clipped_segments, polygon_result)
        return

    draw(segments, clipping_window, clipped_segments, None)

def main():
    def select_file():
        file_path = filedialog.askopenfilename(title="Выберите входной файл")
        if file_path:
            file_label.config(text=f"Выбран файл: {file_path}")
            process_data(file_path, algorithm_var.get())

    root = Tk()
    root.title("Выбор алгоритма отсечения")
    root.geometry("400x200")

    Label(root, text="Выберите алгоритм:", font=("Arial", 14)).pack(pady=10)

    algorithm_var = StringVar(value="Midpoint Algorithm")
    algorithms = ["Midpoint Algorithm", "Polygon Clipping"]
    algorithm_menu = OptionMenu(root, algorithm_var, *algorithms)
    algorithm_menu.pack(pady=10)

    file_label = Label(root, text="Файл не выбран", font=("Arial", 10))
    file_label.pack(pady=10)

    select_button = Button(root, text="Выбрать файл", command=select_file)
    select_button.pack(pady=10)

    root.mainloop()

if __name__ == "__main__":
    main()
