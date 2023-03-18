package TransLiterator;

/**
 * TransliteratorImpl
 */
public class TransliteratorImpl implements Transliterator {

    public String transliterate(String source) {
        String[] arr = source.split(" "); // делим строку на слова
        for (int i = 0; i < arr.length; i++) { // ищем подходящее слово
            if (cyrillic(arr[i]) == true) {
                char[] chArr = arr[i].toCharArray(); // колдуем над подходящим словом
                for (int j = 0; j < chArr.length; j++) {

                }
            }
        }
    }

    // public boolean testStr() {}
    public boolean cyrillic(String word) {
        // проверка первого символа на верхний регистр и на кириллицу
        return true;
    }

    /*
     * что делать в случае ПРИВЕТ! ?
     */
}