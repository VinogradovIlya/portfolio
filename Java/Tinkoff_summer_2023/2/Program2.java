import java.util.Scanner;

/**
 * Program
 * ввод: джуны == колво работ, сеньоры и проверки
 */
public class Program2 {

    public static String input;
    public static String[] arr;

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        input = scan.nextLine();
        scan.close();

        arr = input.split(" ");
        int[] numbers = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            numbers[i] = Integer.parseInt(arr[i]);
        }

        System.out.println(time(numbers));
    }

    static int time(int[] array) {
        int work = array[0] * array[2]; // сколько всего задач на проверку 
        double exactNum = (double) work / array[1]; // среднее время сколько потратят сеньоры на проверку
        int time = (int)Math.ceil(exactNum);
        return time;
    }
}