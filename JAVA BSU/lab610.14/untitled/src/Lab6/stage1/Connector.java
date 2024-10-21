package Lab6.stage1;

import java.io.*;

public class Connector {
    private File file;

    public Connector(String filename) { this.file = new File(filename); }

    public Connector(File file) { this.file = file; }

    public File getFile() { return file; }

    public void write(CargoCarrier[] vehicles) throws IOException {
        FileOutputStream fos = new FileOutputStream(file);
        try (ObjectOutputStream oos = new ObjectOutputStream(fos)) {
            oos.writeInt(vehicles.length);
            for (CargoCarrier vehicle : vehicles) {
                oos.writeObject(vehicle);
            }
            oos.flush();
        }
    }

    public CargoCarrier[] read() throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(file);
        try (ObjectInputStream oin = new ObjectInputStream(fis)) {
            int length = oin.readInt();
            CargoCarrier[] result = new CargoCarrier[length];
            for (int i = 0; i < length; i++) {
                result[i] = (CargoCarrier) oin.readObject();
            }
            return result;
        }
    }
}
