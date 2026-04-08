package by.bsu.tiokrs.lab5.geometry;

import java.util.Comparator;
import java.util.EnumMap;
import java.util.Objects;
import java.util.stream.Stream;

public final class QuadrilateralAnalyzer {
    private QuadrilateralAnalyzer() {
    }

    public static QuadrilateralAnalysisResult analyze(Quadrilateral[] quadrilaterals) {
        Objects.requireNonNull(quadrilaterals, "quadrilaterals");

        EnumMap<QuadrilateralType, QuadrilateralGroupStats> result = new EnumMap<>(QuadrilateralType.class);
        for (QuadrilateralType type : QuadrilateralType.values()) {
            Quadrilateral[] group = Stream.of(quadrilaterals)
                    .peek(q -> Objects.requireNonNull(q, "quadrilateral"))
                    .filter(q -> q.type() == type)
                    .toArray(Quadrilateral[]::new);
            result.put(type, buildStats(group));
        }
        return new QuadrilateralAnalysisResult(result);
    }

    private static QuadrilateralGroupStats buildStats(Quadrilateral[] group) {
        if (group.length == 0) {
            return new QuadrilateralGroupStats(0, null, null, null, null);
        }

        Comparator<Quadrilateral> byArea = Comparator.comparingDouble(Quadrilateral::area);
        Comparator<Quadrilateral> byPerimeter = Comparator.comparingDouble(Quadrilateral::perimeter);

        return new QuadrilateralGroupStats(
                group.length,
                Stream.of(group).min(byArea).orElseThrow(),
                Stream.of(group).max(byArea).orElseThrow(),
                Stream.of(group).min(byPerimeter).orElseThrow(),
                Stream.of(group).max(byPerimeter).orElseThrow()
        );
    }
}
