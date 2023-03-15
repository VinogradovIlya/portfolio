/**
 * StatsAccumulatorImpl
 */
public class StatsAccumulatorImpl implements StatsAccumulator {

    private int min;
    private int max;
    private int count = 0;
    private double avgSum = 0;

    public StatsAccumulatorImpl() {
        this.min = 0;
        this.max = 0;
        this.count = 0;
        this.avgSum = 0;
    }

    public void add(int value) {
        setMin(value);
        setMax(value);
        setCount();
        setAvgSum(value);
    }

    public int getMin() {
        return min;
    }

    public int getMax() {
        return max;
    }

    public int getCount() {
        return count;
    }

    public Double getAvg() {
        return avgSum / count;
    }

    public void setMin(int min) {
        if (this.min > min)
            this.min = min;
    }

    public void setMax(int max) {
        if (this.max < max)
            this.max = max;
    }

    public void setCount() {
        this.count++;
    }

    public void setAvgSum(int value) {
        this.avgSum += (double) value;
    }
}