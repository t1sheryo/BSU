package by.bsu.tiokrs.lab5.geometry;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

class QuadrilateralAnalyzerTest {
    @Test
    void analyzeCountsFiguresByTypeAndFindsExtremes() {
        Quadrilateral smallSquare = new Quadrilateral(0, 0, 1, 0, 1, 1, 0, 1);
        Quadrilateral bigSquare = new Quadrilateral(0, 0, 3, 0, 3, 3, 0, 3);
        Quadrilateral rectangle = new Quadrilateral(0, 0, 4, 0, 4, 2, 0, 2);
        Quadrilateral rhombus = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(4, 3),
                new Point2D(8, 0),
                new Point2D(4, -3)
        );
        Quadrilateral arbitrary = new Quadrilateral(0, 0, 4, 1, 3, 5, -1, 3);

        QuadrilateralAnalysisResult result = QuadrilateralAnalyzer.analyze(new Quadrilateral[]{
                rectangle, bigSquare, arbitrary, rhombus, smallSquare
        });

        QuadrilateralGroupStats squareStats = result.statsFor(QuadrilateralType.SQUARE);
        assertEquals(2, squareStats.count());
        assertEquals(smallSquare.area(), squareStats.minArea().area(), 1e-12);
        assertEquals(bigSquare.area(), squareStats.maxArea().area(), 1e-12);
        assertEquals(smallSquare.perimeter(), squareStats.minPerimeter().perimeter(), 1e-12);
        assertEquals(bigSquare.perimeter(), squareStats.maxPerimeter().perimeter(), 1e-12);

        assertEquals(1, result.statsFor(QuadrilateralType.RECTANGLE).count());
        assertEquals(1, result.statsFor(QuadrilateralType.RHOMBUS).count());
        assertEquals(1, result.statsFor(QuadrilateralType.ARBITRARY).count());
    }

    @Test
    void analyzeReturnsEmptyStatsForMissingGroup() {
        QuadrilateralAnalysisResult result = QuadrilateralAnalyzer.analyze(new Quadrilateral[]{
                new Quadrilateral(0, 0, 2, 0, 2, 2, 0, 2)
        });

        QuadrilateralGroupStats rhombusStats = result.statsFor(QuadrilateralType.RHOMBUS);
        assertEquals(0, rhombusStats.count());
        assertTrue(rhombusStats.isEmpty());
        assertEquals(null, rhombusStats.minArea());
        assertEquals(null, rhombusStats.maxArea());
    }

    @Test
    void analyzeRejectsNullArrayAndNullElements() {
        assertThrows(NullPointerException.class, () -> QuadrilateralAnalyzer.analyze(null));
        assertThrows(NullPointerException.class, () -> QuadrilateralAnalyzer.analyze(new Quadrilateral[]{
                new Quadrilateral(0, 0, 1, 0, 1, 1, 0, 1),
                null
        }));
    }
}
