import java.lang.Math.*;
import java.sql.SQLOutput;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        System.out.println("Print x, k values: ");
        double x = 0;
        int k = 0;
        int deg = 2, fact = 0;
        boolean sign = false;

        Scanner in = new Scanner(System.in);
        x = in.nextDouble();
        k = in.nextInt();

        double variable = 1, sum = 1;
        while(true){

            //double num = variable * x * x;
            variable = (variable * x * x) / ((fact + 1) * (fact + 2));
            fact += 2;
            deg += 2;

            double border = 1 / Math.pow(10, k);
            if(variable < border){
                break;
            }

            if(sign) {
                sum += variable;
                sign = false;
            }
            else {
                sum -= variable;
                sign = true;
            }
        }

        double MathRes = Math.cos(x);
        String format = "%." + k + "f";

        System.out.print("Your result: ");
        System.out.printf(format, sum);
        System.out.print("\nMath library result: ");
        System.out.printf(format, MathRes);
    }
}