package DatedMap;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * DatedMapTest
 */
public class DatedMapTest {

    public static void main(String[] args) {
        Map<String, String> testMap = new HashMap<>();
        Map<String, DatedMapImpl> newMap = new HashMap<>();

        testMap.put("A", "alpha");
        testMap.put("B", "beta");
        testMap.put("C", "cent");

        System.out.println(testMap.get("A"));
        System.out.println(testMap.get("B"));
        System.out.println(testMap.get("C"));
        System.out.println();

        System.out.println(testMap.containsKey("A"));
        System.out.println(testMap.containsKey("D"));
        System.out.println();

        System.out.println(testMap.get("B"));
        System.out.println(testMap.remove("B"));
        System.out.println(testMap.containsKey("B"));
        System.out.println();

        System.out.println(testMap.keySet());
        System.out.println(newMap.entrySet());
        System.out.println();

        for (Map.Entry<String, String> entry : testMap.entrySet()) {
            newMap.put(entry.getKey(), new DatedMapImpl(entry.getValue()));
        }
        System.out.println(newMap.entrySet());
        System.out.println(newMap.get("A").getKeyLastInsertionDate(""));
        System.out.println(newMap.get("A").getKeyLastInsertionDate("A"));
    }
}