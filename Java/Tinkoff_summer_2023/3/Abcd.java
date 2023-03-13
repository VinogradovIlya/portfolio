import java.util.Scanner;

/**
 * Abcd
 */
public class Abcd {

    public static int size;
    public static String str;

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        size = scan.nextInt();
        str = scan.nextLine();
        scan.close();

        System.out.println(size);
        System.out.println(str);
    }
}