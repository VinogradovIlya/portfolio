package FileSort;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

public class Sorter {

    public File sortFile(File dataFile) throws IOException {
        int blockSize = 1024 * 1024 /* * 1024 */; // размер блока в байтах

        // разбиваем входной файл на блоки и сохраняем в список
        List<File> blocks = new ArrayList<>();
        try (RandomAccessFile sourceFile = new RandomAccessFile(dataFile, "r")) {
            byte[] buffer = new byte[blockSize];
            int blockNumber = 0;
            int bytesRead = sourceFile.read(buffer);

            while (bytesRead > 0) {
                File blockFile = new File("block_" + blockNumber + ".txt");
                try (FileOutputStream outputStream = new FileOutputStream(blockFile)) {
                    outputStream.write(buffer, 0, bytesRead);
                }
                blocks.add(blockFile);
                blockNumber++;
                bytesRead = sourceFile.read(buffer);
            }
        }

        // сортируем содержимое блоков и записываем результат в выходной файл
        File sortedFile = new File("sorted_file.txt");
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(sortedFile))) {
            BufferedReader[] readers = new BufferedReader[blocks.size()];
            for (int i = 0; i < blocks.size(); i++) {
                readers[i] = new BufferedReader(new FileReader(blocks.get(i)));
            }

            PriorityQueue<Long> queue = new PriorityQueue<>();

            for (int i = 0; i < readers.length; i++) {
                Long line = Long.valueOf(readers[i].readLine()).longValue();
                if (line != null) {
                    queue.add(line);
                }
            }

            List<Long> result = new ArrayList<>();

            while (!queue.isEmpty()) {
                String min = queue.poll().toString();
                writer.write(min);
                writer.newLine();

                boolean found = false;
                while (!found && !queue.isEmpty()) {
                    int index = findBlockIndex(readers, min);
                    String nextLine = readers[index].readLine();

                    if (nextLine != null) {
                        found = true;
                        queue.add(Long.valueOf(nextLine));
                    } else {
                        min = queue.peek().toString();
                        result.add(queue.poll().longValue());
                    }
                }
            }

            for (int i = 0; i < readers.length; i++) {
                readers[i].close();
            }

            // удаляем временные файлы
            for (File block : blocks) {
                block.delete();
            }

            return dataFile;
        }
    }

    private static int findBlockIndex(BufferedReader[] readers, String line)
            throws IOException {
        for (int i = 0; i < readers.length; i++) {
            if (readers[i].ready()) {
                String nextLine = readers[i].readLine();
                if (nextLine != null && nextLine.equals(line)) {
                    return i;
                }
            }
        }
        // Отладочная информация:
        System.out.println("Line not found: " + line);
        for (int i = 0; i < readers.length; i++) {
            System.out.println("Readers[" + i + "]: " + readers[i].readLine());
        }

        throw new IllegalArgumentException("Line not found in any block");
    }
}
// String inputFileName = dataFile.toString();
// try {
// // Чтение строк из файла и преобразование в числа
// BufferedReader reader = new BufferedReader(new FileReader(inputFileName));
// ArrayList<Long> numbers = new ArrayList<Long>();
// String line;
// while ((line = reader.readLine()) != null) {
// numbers.add(Long.valueOf(line));
// }
// reader.close();
// // Сортировка чисел по возрастанию
// Collections.sort(numbers);
// // Запись отсортированных чисел в новый файл
// File sortedFile = new File("sorted_file.txt");
// FileWriter writer = new FileWriter(sortedFile);
// for (Long sortedNumber : numbers) {
// writer.write(sortedNumber + "\n");
// }
// writer.close();
// return sortedFile;
// } catch (IOException e) {
// System.out.println("Произошла ошибка: " + e.getMessage());
// return null;
// }