import java.util.Scanner;

/**
 * Stars
 */
public class Stars {

    public static void main(String[] args) {
        String str = null;
        String[] arr;

        try (Scanner scan = new Scanner(System.in)) {
            str = scan.nextLine();
        } finally {
            arr = str.split(" ");
            int num1 = Integer.parseInt(arr[0]);
            int num2 = Integer.parseInt(arr[1]);

            for (int i = 0; i < num1; i++) {
                for (int j = 0; j < num2; j++) {
                    System.out.print(arr[2]);
                }
                System.out.println();
            }
        }
    }
}