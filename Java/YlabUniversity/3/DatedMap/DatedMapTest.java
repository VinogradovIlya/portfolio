package DatedMap;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * DatedMapTest
 */
public class DatedMapTest {

    public static void main(String[] args) {
        Map<String, DatedMapImpl> testMap = new HashMap<>(); // 1
        // Map<String, String> testMap = new HashMap<>();

        // testMap.put("A", "alpha");
        // testMap.put("B", "beta");
        testMap.put("C", new DatedMapImpl("test")); // 1

        System.out.println(testMap.get("A"));
        System.out.println(testMap.get("B"));
        System.out.println();

        System.out.println(testMap.containsKey("A"));
        System.out.println(testMap.containsKey("C"));
        System.out.println();

        System.out.println(testMap.get("B"));
        System.out.println(testMap.remove("B"));
        System.out.println(testMap.containsKey("B"));
        System.out.println();

        System.out.println(testMap.keySet());
        System.out.println();

        System.out.println(testMap.get("C").getDate()); // 1
        // System.out.println(testMap.getKeyLastInsertionDate("C"));
    }
}