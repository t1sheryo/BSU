package warehouse;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
class ProductIndex {
    private final Map<Integer, Long> warehouseIndex = new HashMap<>();
    private final Map<Integer, Long> productCodeIndex = new HashMap<>();
    private final Map<Date, Long> arrivalDateIndex = new HashMap<>();
    private final Map<Integer, Long> shelfLifeIndex = new HashMap<>();

    public void addIndex(Product product, long position) {
        warehouseIndex.put(product.getWarehouseNumber(), position);
        productCodeIndex.put(product.getProductCode(), position);
        arrivalDateIndex.put(product.getArrivalDate(), position);
        shelfLifeIndex.put(product.getShelfLifeDays(), position);
    }

    public Long getIndexByWarehouseNumber(int warehouseNumber) {
        return warehouseIndex.get(warehouseNumber);
    }

    public Long getIndexByProductCode(int productCode) {
        return productCodeIndex.get(productCode);
    }

    public Long getIndexByArrivalDate(Date date) {
        return arrivalDateIndex.get(date);
    }

    public Long getIndexByShelfLife(int shelfLifeDays) {
        return shelfLifeIndex.get(shelfLifeDays);
    }

    public Collection<Long> getAllIndexes() {
        return warehouseIndex.values();
    }
}
