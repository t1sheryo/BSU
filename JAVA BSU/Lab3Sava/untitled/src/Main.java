import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        String str = "";
        Scanner input = new Scanner(System.in);

        str = input.nextLine();

        ArrayList<StringBuilder> arr = new ArrayList<>();

        boolean cons = false, vowel = false;
        StringBuilder s = new StringBuilder();
        StringBuilder tmp = new StringBuilder();

        for(int i = 0; i < str.length(); ++i){
            while(i < str.length()){
                if(!cons || !vowel) {
                    if (isVowel(str.charAt(i))) {
                        vowel = true;
                        tmp.append(str.charAt((i)));
                    } else if (isConsonant(str.charAt(i))) {
                        cons = true;
                        tmp.append(str.charAt(i));
                    }
                    i++;
                }
                else{
                    break;
                }
            }
            if(!cons || !vowel){
                StringBuilder per = new StringBuilder();
                per = arr.getLast();
                per.append(tmp);
                arr.removeLast();
                arr.add(per);
            }
            while(i + 3 < str.length()) {
                if (isConsonant(str.charAt(i + 1)) && isConsonant(str.charAt(i + 2))) {
                    tmp.append(str.charAt(i));
                    ++i;
                } else {
                    break;
                }
            }
            arr.add(tmp);
            tmp.delete(0, tmp.length() - 1);
            cons = false;
            vowel = false;
        }
        for(int i = 0; i < arr.size(); ++i){
            System.out.println(arr.get(i));
            System.out.println("-");
        }
    }
    public static boolean isVowel(char ch) {
        return "AEIOUaeiou".indexOf(ch) != -1;
    }

    // Метод для проверки, является ли символ согласной
    public static boolean isConsonant(char ch) {
        return Character.isLetter(ch) && !isVowel(ch);
    }
}