import java.util.Scanner;
/**
 * 1
 */
public class Zadacha1 {
    public static void main(String[] args) {
        System.out.println("Написать программу вычисления n-ого треугольного числа.");
        Scanner inputScanner = new Scanner(System.in);
        int input = inputScanner.nextInt();
        
        double output = 0.5 * input * (input + 1);
        System.out.println(output);
    }
}