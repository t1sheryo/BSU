package warehouse;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class Product implements Serializable {
    private int warehouseNumber;
    private int productCode;
    private String productName;
    private Date arrivalDate;
    private int shelfLifeDays;
    private int quantity;
    private double pricePerUnit;

    // Конструктор
    public Product(int warehouseNumber, int productCode, String productName, Date arrivalDate, int shelfLifeDays, int quantity, double pricePerUnit) {
        this.warehouseNumber = warehouseNumber;
        this.productCode = productCode;
        this.productName = productName;
        this.arrivalDate = arrivalDate;
        this.shelfLifeDays = shelfLifeDays;
        this.quantity = quantity;
        this.pricePerUnit = pricePerUnit;
    }

    public int getWarehouseNumber() { return warehouseNumber; }
    public int getProductCode() { return productCode; }
    public Date getArrivalDate() { return arrivalDate; }
    public int getShelfLifeDays() { return shelfLifeDays; }

    @Override
    public String toString() {
        return "Product{" +
                "warehouseNumber=" + warehouseNumber +
                ", productCode=" + productCode +
                ", productName='" + productName + '\'' +
                ", arrivalDate=" + arrivalDate +
                ", shelfLifeDays=" + shelfLifeDays +
                ", quantity=" + quantity +
                ", pricePerUnit=" + pricePerUnit +
                '}';
    }
}
