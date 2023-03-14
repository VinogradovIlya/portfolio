/**
 * App
 */
public class App {

    public static void main(String[] args) {
        System.out.println(new SnilsValidatorImpl().validate("01468870570")); // false

        System.out.println(new SnilsValidatorImpl().validate("90114404441")); // true

        System.out.println(new SnilsValidatorImpl().validate("901-440S441")); // false
    }
}