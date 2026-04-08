package by.bsu.tiokrs.lab5.geometry;

public record QuadrilateralGroupStats(
        int count,
        Quadrilateral minArea,
        Quadrilateral maxArea,
        Quadrilateral minPerimeter,
        Quadrilateral maxPerimeter
) {
    public boolean isEmpty() {
        return count == 0;
    }
}
