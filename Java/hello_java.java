package Java;

/**
 * hello_java
 */
public class hello_java {
    public static void main(String[] args) {
       String s = null;
       s = "string is String";
       System.out.println(s);
       int i = 10;
       float f = 10.34f;
       double d = 10.45;
       boolean bool = true ^ false;
       System.out.println(bool);
       var variant = 123.56;
    //    System.out.println(getType(variant)); // ?
        --i;
        System.out.println(i);
        i++;
        System.out.println(i);
        i--;
        System.out.println(i);
        ++i;
        System.out.println(i);
        boolean z = 123 != 234;
        System.out.println(z);
    }
}