import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * insertion_sort
 * https://www.youtube.com/watch?v=jywoZ2XaQoM
 */
public class insertion_sort {

    public static void main(String[] args) {
        int[] array = new int[] {64, 42, 74, 51, 33, 17, 77, 88, 98, 12, 45, 66};
        insertionSort(array);
        System.out.println(Arrays.toString(array));
    }

    public static void insertionSort(int[] array) {
        for (int i = 1; i < array.length; i++) {
            int current = array[i];
            int j = i;
            while (j > 0 && array[j-1] > current) {
                array[j] = array[j-1];
                j--;
            }
            array[j] = current;
        }
    }
}