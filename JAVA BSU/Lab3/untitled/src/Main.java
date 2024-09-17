import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String str = "";
        Scanner input = new Scanner(System.in);

        str = input.nextLine();
        StringBuilder s = new StringBuilder();
        int cnt = 0;
        char sym;
        for(int i = 0; i < str.length(); ++i){
            sym = str.charAt(i);
            cnt++;
            while(i + 1 < str.length()){
                if(sym != str.charAt(i + 1)) break;
                cnt++;
                i++;
            }
            s.append(sym);
            s.append(cnt);
            cnt = 0;
        }
        System.out.println(s);
    }
}