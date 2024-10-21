package Lab6.stage2;

import Lab6.stage1.CargoCarrier;

import java.io.*;

public class Connector {
    private File file;

    public Connector(String filename) { this.file = new File(filename); }

    public Connector(File file) { this.file = file; }

    public File getFile() { return file; }

    public void write(Lab6.stage2.CargoCarrier[] vehicles) throws IOException {
        FileOutputStream fos = new FileOutputStream(file);
        try (ObjectOutputStream oos = new ObjectOutputStream(fos)) {
            oos.writeInt(vehicles.length);
            for (Lab6.stage2.CargoCarrier vehicle : vehicles) {
                oos.writeObject(vehicle);
            }
            oos.flush();
        }
    }

    public Lab6.stage2.CargoCarrier[] read() throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(file);
        try (ObjectInputStream oin = new ObjectInputStream(fis)) {
            int length = oin.readInt();
            Lab6.stage2.CargoCarrier[] result = new Lab6.stage2.CargoCarrier[length];
            for (int i = 0; i < length; i++) {
                result[i] = (Lab6.stage2.CargoCarrier) oin.readObject();
            }
            return result;
        }
    }
}
