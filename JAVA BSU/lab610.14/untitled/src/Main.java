import Lab6.stage2.*;

import java.io.File;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.util.Locale;
import java.util.ResourceBundle;

public class Main {

    static Locale createLocale(String[] args) {
        if (args.length == 2) {
            return new Locale(args[0], args[1]);
        } else if (args.length == 4) {
            return new Locale(args[2], args[3]);
        }
        return null;
    }

    static void setupConsole(String[] args) {
        if (args.length >= 2) {
            if (args[0].equals("-encoding")) {
                try {
                    System.setOut(new PrintStream(System.out, true, args[1]));
                } catch (UnsupportedEncodingException ex) {
                    System.err.println("Unsupported encoding: " + args[1]);
                    System.exit(1);
                }
            }
        }
    }

    public static void main(String[] args) {
        try {
            Locale locale = Locale.getDefault();
            if(args.length >= 2){
                locale = new Locale(args[0], args[1]);
            }

            ResourceBundle bundle = ResourceBundle.getBundle("Msg", locale);

            Connector con = new Connector(new File("stage2.dat"));

            CargoCarrier[] vehicle = new CargoCarrier[5];
            vehicle[0] = new Car(bundle.getString(AppLocale.Ferrari), 320);
            vehicle[1] = new Airplane(bundle.getString(AppLocale.Boeing), 1000);
            vehicle[2] = new Train(bundle.getString(AppLocale.AeroFlot), 600);
            vehicle[3] = new Car(bundle.getString(AppLocale.Mazda), 240);
            vehicle[4] = new Car(bundle.getString(AppLocale.Banan));

            con.write(vehicle);
            CargoCarrier[] returnedVehicles = con.read();
            System.out.println(bundle.getString(AppLocale.CargoCarrier) + ": ");

            for(int i = 0; i < returnedVehicles.length; ++i){
                System.out.println(returnedVehicles[i]);
            }

        } catch (Exception e){
            System.out.println(e) ;
        }

    }
}