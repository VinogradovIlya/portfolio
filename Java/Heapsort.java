// https://www.youtube.com/watch?v=DU1uG5310x0
// https://habr.com/ru/company/otus/blog/460087/

public class Heapsort {
    public void sort(int arr[]) {
        int n = arr.length;
        // построение кучи (перегруппировка массива)
        for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
        
        // поочередно извлекаем элементы из кучи
        for (int i = n - 1; i >= 0; i--) {
            // перемещаем текущий корень в конец
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            //вызываем процедуру heapify на уменьшенной куче 
            heapify(arr, i, 0);
        }
    }
    
    /**  процедура преобразования в двоичную кучу поддерева с корневым узлом i, 
     * что яляется индексом в arr[]. n -- размер кучи*/ 
    void heapify(int arr[], int n, int i) {
        int largest = i; // инициалиризируем наибольший элемент как корень
        int l = 2*i + 1; // левый = 2*i + 1
        int r = 2*i + 2; // правый = 2*i + 2

        //если левый дочерний элемент больше корня
        if (l < n && arr[l] > arr[largest]) largest = l;

        // если правый дочерний элемент больше, чем самый большой элемент на данный момент
        if (r < n && arr[r] > arr[largest]) largest = r;

        // если самый большой элемент не корень
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            // рекурсивно преобразуем в двоичную кучу затронутое поддерево
            heapify(arr, n, largest);
        }
    }

    /* вспомогательная функция для вывода на экран массива размера n */
    static void printArray(int arr[]) {
        int n = arr.length;
        for (int i = 0; i < n; ++i) System.out.print(arr[i] + " ");
        System.out.println();
    }

    // управляющая программа
    public static void main(String[] args) {
        int arr[] = {12, 11, 13, 5, 7, 10, 23, 3, 17};
        printArray(arr);
        int n = arr.length;

        Heapsort ob = new Heapsort();
        ob.sort(arr);

        System.out.println("Sorted array is: ");
        printArray(arr);
    }
}