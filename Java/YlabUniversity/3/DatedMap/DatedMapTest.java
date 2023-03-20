package DatedMap;

public class DatedMapTest {

    public static void main(String[] args) {

        DatedMapImpl datedMapImpl = new DatedMapImpl();
        datedMapImpl.put("A", "alpha");
        datedMapImpl.put("B", "beta");
        datedMapImpl.put("C", "cent");

        System.out.println(datedMapImpl.get("A"));
        System.out.println(datedMapImpl.get("B"));
        System.out.println(datedMapImpl.get("C"));
        System.out.println();

        System.out.println(datedMapImpl.containsKey("A"));
        System.out.println(datedMapImpl.containsKey("D"));
        System.out.println();

        System.out.println(datedMapImpl.keySet());
        datedMapImpl.remove("B");
        System.out.println(datedMapImpl.keySet());
        System.out.println();

        System.out.println(datedMapImpl.getKeyLastInsertionDate("A"));
        System.out.println(datedMapImpl.getKeyLastInsertionDate("D"));
    }
}