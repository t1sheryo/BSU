package Lab6.stage2;

import java.util.*;

public class AppLocale {
    private static final String strMsg = "Msg";
    private static Locale loc = Locale.getDefault();
    private static ResourceBundle res =
            ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );

     static Locale get() {
        return AppLocale.loc;
    }

     public static void set(Locale loc) {
        AppLocale.loc = loc;
        res = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
    }

    static ResourceBundle getBundle() {
        return AppLocale.res;
    }

     public static String getString(String key) {
        return AppLocale.res.getString(key);
    }

    public static final String CargoCarrier = "CargoCarrier";
    public static final String type = "type";
    public static final String speed = "speed";
    public static final String car = "car";
    public static final String airplane = "airplane";
    public static final String train = "train";
    public static final String model = "model";
    public static final String Ferrari = "ferrari";
    public static final String Boeing = "boeing";
    public static final String AeroFlot = "aeroflot";
    public static final String Mazda = "mazda";
    public static final String Banan = "banan";
}
