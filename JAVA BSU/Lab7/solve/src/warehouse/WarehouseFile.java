package warehouse;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class WarehouseFile implements AutoCloseable {
    private final RandomAccessFile file;
    private final ProductIndex index;

    public WarehouseFile(String filename) throws IOException {
        this.file = new RandomAccessFile(filename, "rw");
        this.index = new ProductIndex();
    }

    public void addProduct(Product product) throws IOException {
        long position = file.length();
        file.seek(position);

        // Use a ByteArrayOutputStream to temporarily hold the serialized object
        ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
        try (ObjectOutputStream objectOut = new ObjectOutputStream(byteStream)) {
            objectOut.writeObject(product); // Serialize the product into byteStream
            objectOut.flush();
        }

        // Write the byte array to the RandomAccessFile
        byte[] productBytes = byteStream.toByteArray();
        file.writeInt(productBytes.length); // Write the length first
        file.write(productBytes); // Then write the actual data

        index.addIndex(product, position); // Store the position in the index
    }

    public void displayAllProducts(){
        try {
            file.seek(0);
            while (file.getFilePointer() < file.length()) {
                Product product = readProductFromFile();
                if (product != null) {
                    System.out.println(product);
                }
            }
        }catch(IOException ex){
            System.out.println(ex.getMessage());
        }
        catch (ClassNotFoundException ex){
            System.out.println(ex.getMessage());
        }
    }

    public void displaySortedProducts(Comparator<Product> comparator) throws IOException, ClassNotFoundException {
        List<Product> products = new ArrayList<>();
        file.seek(0);
        while (file.getFilePointer() < file.length()) {
            Product product = readProductFromFile();
            if (product != null) {
                products.add(product);
            }
        }
        products.stream().sorted(comparator).forEach(System.out::println);
    }

    public Product findProductByWarehouseNumber(int warehouseNumber) throws IOException, ClassNotFoundException {
        Long position = index.getIndexByWarehouseNumber(warehouseNumber);
        return position != null ? readProductAtPosition(position) : null;
    }

    public Product findProductByProductCode(int warehouseNumber) throws IOException, ClassNotFoundException {
        Long position = index.getIndexByProductCode(warehouseNumber);
        return position != null ? readProductAtPosition(position) : null;
    }

    private Product readProductAtPosition(long position) throws IOException, ClassNotFoundException {
        file.seek(position);
        return readProductFromFile();
    }

    private Product readProductFromFile() throws IOException, ClassNotFoundException {
        if (file.getFilePointer() >= file.length()) return null;

        int length = file.readInt();
        byte[] productBytes = new byte[length];
        file.readFully(productBytes);

        try (ObjectInputStream objectIn = new ObjectInputStream(new ByteArrayInputStream(productBytes))) {
            return (Product) objectIn.readObject();
        }
    }

    public void deleteProductByWarehouseNumber(int warehouseNumber) throws IOException, ClassNotFoundException {
        Long position = index.getIndexByWarehouseNumber(warehouseNumber);
        if (position != null) {
            file.seek(position);
            file.writeInt(0); // Mark product as deleted with a length of zero
        }
    }

    public void close() throws IOException {
        file.close();
    }
}
