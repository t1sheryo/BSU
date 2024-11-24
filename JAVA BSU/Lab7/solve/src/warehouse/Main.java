package warehouse;

import java.util.Date;

public class Main {
    public static void main(String[] args) {
          try (WarehouseFile warehouseFile = new WarehouseFile("warehouse.dat")) {
            warehouseFile.addProduct(new Product(1, 101, "ProductA", new Date(), 30, 100, 10.0));
            warehouseFile.addProduct(new Product(2, 102, "ProductB", new Date(), 20, 150, 20.0));

            System.out.println("Все товары:");
            warehouseFile.displayAllProducts();

            Product foundProduct = warehouseFile.findProductByWarehouseNumber(1);
            System.out.println("Найденный товар: " + foundProduct);

            warehouseFile.deleteProductByWarehouseNumber(1);

            Product deletedProduct = warehouseFile.findProductByWarehouseNumber(2);
            System.out.println("Удаленный товар: " + deletedProduct);
        } catch (Exception e) {
            System.out.println("Произошла ошибка: " + e.getMessage());
        }
    }
}