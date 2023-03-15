/**
 * StatsAccumulator
 */
public interface StatsAccumulator {

    void add(int value);

    int getMin();

    int getMax();

    int getCount();

    Double getAvg();
}