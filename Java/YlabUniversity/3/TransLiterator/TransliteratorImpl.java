package TransLiterator;

import java.util.HashMap;
import java.util.Map;

/**
 * TransliteratorImpl
 */
public class TransliteratorImpl implements Transliterator {

    private static final Map<Character, String> alphabet = new HashMap<>();

    static { // инициализация алфавита
        alphabet.put('А', "A");
        alphabet.put('Б', "B");
        alphabet.put('В', "V");
        alphabet.put('Г', "G");
        alphabet.put('Д', "D");
        alphabet.put('Е', "E");
        alphabet.put('Ё', "E");
        alphabet.put('Ж', "ZH");
        alphabet.put('З', "Z");
        alphabet.put('И', "I");
        alphabet.put('Й', "I");
        alphabet.put('К', "K");
        alphabet.put('Л', "L");
        alphabet.put('М', "M");
        alphabet.put('Н', "N");
        alphabet.put('О', "O");
        alphabet.put('П', "P");
        alphabet.put('Р', "R");
        alphabet.put('С', "S");
        alphabet.put('Т', "T");
        alphabet.put('У', "U");
        alphabet.put('Ф', "F");
        alphabet.put('Х', "KH");
        alphabet.put('Ц', "TS");
        alphabet.put('Ч', "CH");
        alphabet.put('Ш', "SH");
        alphabet.put('Щ', "SHCH");
        alphabet.put('Ы', "Y");
        alphabet.put('Ь', "");
        alphabet.put('Ъ', "IE");
        alphabet.put('Э', "E");
        alphabet.put('Ю', "IU");
        alphabet.put('Я', "IA");
    }

    public String transliterate(String source) {
        StringBuilder stringBuilder = new StringBuilder();
        char[] chArr = source.toCharArray();
        for (int i = 0; i < chArr.length; i++) {
            if (alphabet.containsKey(chArr[i])) {
                stringBuilder.append(
                        alphabet.get(chArr[i]));
            } else {
                stringBuilder.append(chArr[i]);
            }
        }
        return stringBuilder.toString();
    }
}