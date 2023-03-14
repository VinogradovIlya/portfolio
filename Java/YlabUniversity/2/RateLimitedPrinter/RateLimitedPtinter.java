/**
 * RateLimitedPtinter
 */
public class RateLimitedPtinter {

    private int interval;

    public RateLimitedPtinter(int interval) {
        this.interval = interval;
    }
    
    public void print(String message) {
        System.out.println(message);
    }

    public int getInterval() {
        return interval;
    }
}