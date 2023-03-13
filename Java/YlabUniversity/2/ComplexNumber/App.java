/**
 * App
 */
public class App {

    public static void main(String[] args) {

        ComplexNum cn = new ComplexNum();
        System.out.println(toString(cn));

        ComplexNum cn1 = new ComplexNum(4, 3);
        System.out.print(toString(cn1));
        System.out.println(" модуль числа " + cn1.modul());


        ComplexNum cn2 = new ComplexNum(10);
        System.out.println(toString(cn2));

        System.out.println("результат сложения второго числа с третьим " +
                toString(cn1.sum(cn2)));
        System.out.println("результат вычитания третьего числа из второго " +
                toString(cn1.sub(cn2)));
        System.out.println("результат умножения второго числа с третьим " +
                toString(cn1.mult(cn2)));
    }

    static public String toString(ComplexNum complexNum) {
        return complexNum.getDeystv() + " " + "+" + " " + complexNum.getMnim() + "i";
    }
}