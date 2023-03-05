import java.util.Arrays;
import java.util.Scanner;
import java.util.StringBuilder;

public class Program {

    public static void main(String[] args) {
        String input = null;
        String[] arr;
        String temp;
        String reversTemp;

        try (Scanner scan = new Scanner(System.in)) {
            input = scan.nextLine();
        } finally {
            arr = input.split(" ");
            Arrays.sort(arr);

            temp = String.join(" ", arr);

            reversTemp = new StringBuilder(temp).reverse().toString();

            if (input.equals(temp) || input.equals(reversTemp)) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}