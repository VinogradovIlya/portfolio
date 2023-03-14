/**
 * 
 */
public class Main {

    public static void main(String[] args) throws InterruptedException {

        RateLimitedPtinter rlp = new RateLimitedPtinter(1000);

        long timeStart = System.currentTimeMillis();
        long timePrint = timeStart + rlp.getInterval();

        for (int i = 0; i < 1_000_000_000; i++) {
            long timeNow = System.currentTimeMillis();

            if (timeNow >= timePrint) {
                rlp.print(String.valueOf(i));
                timeStart = System.currentTimeMillis();
                // Thread.sleep(rlp.getInterval());
            }

                Thread.sleep(rlp.getInterval());
        }
        System.out.println(System.currentTimeMillis());
    }
}