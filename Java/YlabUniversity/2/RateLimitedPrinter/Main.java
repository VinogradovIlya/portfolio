/**
 * 
 */
public class Main {

    public static void main(String[] args) throws InterruptedException {

        RateLimitedPtinter rlp = new RateLimitedPtinter(1000);

        for (int i = 0; i < 1_000_000_000; i++) {
            rlp.print(String.valueOf(i));
        }
    }
}