import java.math.BigInteger;
import java.util.Scanner;
import java.util.Formatter.BigDecimalLayoutForm;

/**
 * Pell
 */
public class Pell {

    public static void main(String[] args) {
        int n;
        try (Scanner scan = new Scanner(System.in)) {
            n = scan.nextInt();
            System.out.println(pellNumber(n));
        }
    }

    static long pellNumber(int number) {
        if (number == 0)
            return 0;
        else if (number == 1)
            return 1;
        else
            return 2 * pellNumber(number - 1) + pellNumber(number - 2);
    }
}