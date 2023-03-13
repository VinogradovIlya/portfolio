/**
 * SequencesImpl
 */
public class SequencesImpl implements Sequences {

    public void a(int n) {
        for (int i = 1; i <= n * 2; i++) {
            if (i % 2 == 0)
                System.out.println(i);
        }
    }

    public void b(int n) {
        for (int i = 0; i <= n * 2; i++) {
            if (i % 2 != 0)
                System.out.println(i);
        }
    }

    public void c(int n) {
        for (int i = 1; i <= n; i++) {
            System.out.println((int) Math.pow(i, 2));
        }
    }

    public void d(int n) {
        for (int i = 1; i <= n; i++) {
            System.out.println((int) Math.pow(i, 3));
        }
    }

    public void e(int n) {
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0) {
                System.out.println("-1");
            } else {
                System.out.println(1);
            }
        }
    }

    public void f(int n) {
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0)
                System.out.println(i * -1);
            else
                System.out.println(i);
        }
    }

    public void g(int n) {
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0)
                System.out.println((int) Math.pow(i, 2) * -1);
            else
                System.out.println((int) Math.pow(i, 2));
        }
    }

    public void h(int n) {
        for (int i = 1; i <= n; i++) {
            System.out.println(i);
            System.out.println("0");
        }
    }

    public void i(int n) {
        int j = 1;
        for (int i = 1; i <= n; i++) {
            j *= i;
            System.out.println(j);
        }
    }

    public void j(int n) {
        int fib1 = 1, fib2 = 1, fib3;
        System.out.println(fib1);
        System.out.println(fib2);
        for (int i = 2; i < n; i++) {
            fib3 = fib1 + fib2;
            System.out.println(fib3);
            fib1 = fib2;
            fib2 = fib3;
        }
    }
}