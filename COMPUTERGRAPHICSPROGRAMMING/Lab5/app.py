import matplotlib.pyplot as plt
from shapely.geometry import LineString, Polygon
from shapely.geometry.polygon import orient

segments = [
    [(50, 50), (350, 250)],
    [(100, 300), (500, 500)],
    [(200, 50), (800, 300)],
]

clipping_window = [(150, 100), (600, 100), (600, 400), (150, 400)]


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

    if isinstance(clipped, Polygon):
        return [(p[0], p[1]) for p in clipped.exterior.coords]

    return None


def clip_polygon(polygon, clipping_window):
    polygon_shape = Polygon(polygon)
    clipping_polygon = Polygon(clipping_window)

    clipped = polygon_shape.intersection(clipping_polygon)

    if clipped.is_empty:
        return None

    if isinstance(clipped, Polygon):
        return [(p[0], p[1]) for p in clipped.exterior.coords]

    return None


clipped_segments = []
for segment in segments:
    clipped_segment = clip_segment(segment, clipping_window)
    if clipped_segment:
        clipped_segments.append(clipped_segment)

draw(segments, clipping_window, clipped_segments)
