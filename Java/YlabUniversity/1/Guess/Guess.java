import java.util.Random;
import java.util.Scanner;

public class Guess {

    public static void main(String[] args) {
        int number = new Random().nextInt(100);
        System.out.println(number);
        int maxAttemps = 10;

        System.out.println("я загадал число от 1 до 99. У тебя " + maxAttemps + " попыток отгадать");
        Scanner scan = new Scanner(System.in);
        while (maxAttemps >= 0) {
            int shot = scan.nextInt();
            maxAttemps--;
            if (shot == number) {
                System.out.println("Молодец, ты угадал c " + (10 - maxAttemps) + " попыток");
                break;
            }
            if (shot > number)
                System.out.println("Мое число меньше! У тебя еще " + maxAttemps + " попыток");
            if (shot < number)
                System.out.println("Мое число больше! У тебя еще " + maxAttemps + " попыток");
            if (maxAttemps == 0) {
                System.out.println("Ты не угадал");
                break;
            }
        }
        scan.close();
    }
}