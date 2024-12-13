import matplotlib.pyplot as plt
from shapely.geometry import LineString, Polygon
import tkinter as tk
from tkinter import filedialog, simpledialog
import csv

def load_data_from_file():
    file_path = filedialog.askopenfilename(filetypes=[("CSV Files", "*.csv"), ("Text Files", "*.txt")])
    if not file_path:
        return None, None

    segments = []
    clipping_window = []

    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            if row[0].lower() == "segment":
                segments.append([(float(row[1]), float(row[2])), (float(row[3]), float(row[4]))])
            elif row[0].lower() == "clippingwindow":
                clipping_window.append((float(row[1]), float(row[2])))

    return segments, clipping_window

def manual_input():
    segments = []
    clipping_window = []

    num_segments = simpledialog.askinteger("Input", "Enter the number of line segments:")
    for i in range(num_segments):
        x1 = simpledialog.askfloat(f"Segment {i+1}", "Enter start x:")
        y1 = simpledialog.askfloat(f"Segment {i+1}", "Enter start y:")
        x2 = simpledialog.askfloat(f"Segment {i+1}", "Enter end x:")
        y2 = simpledialog.askfloat(f"Segment {i+1}", "Enter end y:")
        segments.append([(x1, y1), (x2, y2)])

    num_clipping_points = simpledialog.askinteger("Input", "Enter the number of points for the clipping window:")
    for i in range(num_clipping_points):
        x = simpledialog.askfloat(f"Point {i+1}", "Enter x:")
        y = simpledialog.askfloat(f"Point {i+1}", "Enter y:")
        clipping_window.append((x, y))

    return segments, clipping_window

def draw(segments, clipping_window, clipped_segments):
    fig, ax = plt.subplots()

    clipping_polygon = Polygon(clipping_window)
    x, y = clipping_polygon.exterior.xy
    ax.fill(x, y, alpha=0.3, color='green', label='Clipping Region')

    for segment in segments:
        x_vals, y_vals = zip(*segment)
        ax.plot(x_vals, y_vals, color='blue', label='Original Segment')

    for segment in clipped_segments:
        x_vals, y_vals = zip(*segment)
        ax.plot(x_vals, y_vals, color='red', label='Clipped Segment')

    ax.set_xlim(0, 900)
    ax.set_ylim(0, 600)
    ax.set_aspect('equal', adjustable='box')
    ax.legend()
    plt.show()

def clip_segment(segment, clipping_window):
    line = LineString(segment)
    clipping_polygon = Polygon(clipping_window)

    clipped = line.intersection(clipping_polygon)

    if clipped.is_empty:
        return None

    if isinstance(clipped, LineString):
        return [(p[0], p[1]) for p in clipped.coords]

    return None

def main():
    root = tk.Tk()
    root.withdraw()  # Hide the main tkinter window

    choice = simpledialog.askstring("Input", "Enter 'file' to load from file or 'manual' for manual input:")
    if choice.lower() == 'file':
        segments, clipping_window = load_data_from_file()
    elif choice.lower() == 'manual':
        segments, clipping_window = manual_input()
    else:
        print("Invalid choice")
        return

    if not segments or not clipping_window:
        print("No data provided.")
        return

    clipped_segments = []
    for segment in segments:
        clipped_segment = clip_segment(segment, clipping_window)
        if clipped_segment:
            clipped_segments.append(clipped_segment)

    draw(segments, clipping_window, clipped_segments)

if __name__ == "__main__":
    main()


# [(50, 50), (350, 250)],
#     [(100, 300), (500, 500)],
#     [(200, 50), (800, 300)],