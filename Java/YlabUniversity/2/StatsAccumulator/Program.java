/**
 * Program
 */
public class Program {

    public static void main(String[] args) {

        StatsAccumulatorImpl sai = new StatsAccumulatorImpl();

        sai.add(1);
        sai.add(2);

        System.out.println(sai.getAvg());

        sai.add(0);

        System.out.println(sai.getMin());

        sai.add(3);
        sai.add(8);

        System.out.println(sai.getMax());
        System.out.println(sai.getCount());
    }
}