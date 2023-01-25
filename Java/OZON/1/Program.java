import java.util.Scanner;

public class Program {
    public static void main(String[] args) {

        // ввод
        Scanner input = new Scanner(System.in);
        int numberOne = input.nextInt();
        String[] arr = new String[numberOne];
        for (int i = 0; i < numberOne; i++)
        {
            arr[i] = input.nextLine();
        }
        input.close();

        // ответ
        for (String i : arr) {
            System.out.println(math(i));
        }
    }

    static int math(String str)
    {
        String[] newArr = str.split(" ");
        int a = Integer.parseInt(newArr[0]);
        int b = Integer.parseInt(newArr[1]);
        return a + b;
    }
}