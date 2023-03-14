/**
 * RateLimitedPtinter
 */
public class RateLimitedPtinter {

    private int interval;
    private long lastCallTime = 0;

    public RateLimitedPtinter(int interval) {
        this.interval = interval;
    }

    public void print(String message) {
        long startTime = System.currentTimeMillis();
        if (startTime - lastCallTime > getInterval()) {
            lastCallTime = startTime;
            System.out.println(message);
        }
    }

    public int getInterval() {
        return interval;
    }
}