package by.bsu.tiokrs.lab5.geometry;

import java.util.EnumMap;
import java.util.Map;
import java.util.Objects;

public final class QuadrilateralAnalysisResult {
    private final EnumMap<QuadrilateralType, QuadrilateralGroupStats> groups;

    public QuadrilateralAnalysisResult(Map<QuadrilateralType, QuadrilateralGroupStats> groups) {
        Objects.requireNonNull(groups, "groups");
        this.groups = new EnumMap<>(QuadrilateralType.class);
        for (QuadrilateralType type : QuadrilateralType.values()) {
            QuadrilateralGroupStats stats = groups.get(type);
            this.groups.put(type, stats == null ? new QuadrilateralGroupStats(0, null, null, null, null) : stats);
        }
    }

    public QuadrilateralGroupStats statsFor(QuadrilateralType type) {
        return groups.get(Objects.requireNonNull(type, "type"));
    }

    public Map<QuadrilateralType, QuadrilateralGroupStats> groups() {
        return Map.copyOf(groups);
    }
}
