/**
 * towers
 */
public class towers {

    public static void main(String[] args) {
        int count = 3;
        moveRing('1', '3', '2', count);
    }

    public static void moveRing(char a, char b, char c, int count) {
    	if (count > 1) moveRing(a, c, b, count - 1);
        System.out.println(String.format("from %s to %s",a,b));
        if (count > 1) moveRing(c, b, a, count - 1);
    }
}