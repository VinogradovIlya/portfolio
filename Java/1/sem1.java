import java.util.Scanner;

/*  b > a, a, b, c, d - натуральные
На вход некоторому исполнителю подаётся два числа (a, b). 
У исполнителя есть две команды
- команда 1 (к1): увеличить а в с раз, а умножается на c
- команда 2 (к2): увеличить на d, к a прибавляется d
написать программу, которая выдаёт набор команд, позволяющий число a превратить в число b или сообщить, что это невозможно
Пример 1: а = 1, b = 7, c = 2, d = 1
ответ: к2, к2, к2, к2, к2, к2, k2 или к1, к1, к2, к2, к2 
Можно начать с более простого – просто подсчёта общего количества вариантов 
Пример 2: а = 11, b = 7, c = 2, d = 1
ответ: нет решения. 
*Подумать над тем, как сделать минимальное количество команд*/

public class sem1 {
    public static void main(String[] args) {
        Scanner myScanner = new Scanner(System.in);
        System.out.print("a = ");
        int a = myScanner.nextInt();
        System.out.print("b = ");
        int b = myScanner.nextInt();
        System.out.print("c = ");
        int c = myScanner.nextInt();
        System.out.print("d = ");
        int d = myScanner.nextInt();
        System.out.println();

        while (a != b) {
            int min1, min2 = 0;
            int step1 = a * c;
            int step2 = a + d;
            min1 = b - step1;
            min2 = b - step2;
            if (step1 >= step2) {
                a = step1;
                System.out.printf("a * %d = %d\n", c, a);
            }
            else {
                a = step2;
                System.out.printf("a + %d = %d\n", d, a);
            }

            if (min1 > min2) {
                a *=c;
                System.out.printf("a * %d = %d\n", c, a);
            }
            else {
                a += d;
                System.out.printf("a + %d = %d\n", d, a);
            }
        }
    }
}