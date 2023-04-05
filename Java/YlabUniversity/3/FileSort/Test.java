package FileSort;

import java.io.File;
import java.io.IOException;

public class Test {

    public static void main(String[] args) throws IOException {
        Long time = System.currentTimeMillis();

        File dataFile = new Generator().generate("data.txt", /* 1000_000_000 */1_000_000);
        System.out.println(new Validator(dataFile).isSorted());
        File sortedFile = new Sorter().sortFile(dataFile);
        System.out.println(new Validator(sortedFile).isSorted());

        System.out.println(System.currentTimeMillis() - time);
    }
}